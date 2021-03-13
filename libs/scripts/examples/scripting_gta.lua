--[[
    Scripting examples using the LuaGLM binding API.

@NOTE: Examples not designed with performance in mind.
@LICENSE
    See Copyright Notice in lua.h
--]]
local glm = glm

--[[
    Example 1: ScreenPositionToCameraRay: gluUnProject implemented with data
    extracted from GTA V script natives.

    Details: Multiply a pixel position by the inverse of the cameras view and
    projection matrix. This implementation requires the screen coordinates to be
    on a [-1, 1] scale.
--]]
function ScreenPositionToCameraRay(screenX, screenY)
    local pos = GetFinalRenderedCamCoord()
    local rot = glm.rad(GetFinalRenderedCamRot(2))

    local q = glm.quatEulerAngleZYX(rot.z, rot.y, rot.x)
    return pos,glm.rayPicking(
        q * glm.forward(),
        q * glm.up(),
        glm.rad(GetFinalRenderedCamFov()),
        GetAspectRatio(true),
        0.10000, -- GetFinalRenderedCamNearClip(),
        10000.0, -- GetFinalRenderedCamFarClip(),
        screenX * 2 - 1, -- scale mouse coordinates from [0, 1] to [-1, 1]
        screenY * 2 - 1
    )
end

--[[
    Example 2: Convert a surface normal (often the result of a raycast) to a
    rotation usable by DrawMarker()

@NOTE This is a right-handed computation.
--]]
function SurfaceNormalToMarkerRotation(normal)
    local quat_eps = 1E-2
    local q = nil

    -- If the surface normal is upwards or downwards, rotate the Z (heading) of
    -- the quaternion so any rendered texture/decal is directed towards the
    -- client camera.
    if glm.approx(glm.abs(normal.z), 1.0, quat_eps) then
        local camRot = GetFinalRenderedCamRot(2)
        local counterRotation = (glm.sign(normal.z) * -camRot.z) - 90.0

        q = glm.quatlookRotation(normal, glm.right())
        q = q * quat(counterRotation, glm.up())
    else
        q = glm.quatlookRotation(normal, glm.up())
        if glm.approx(normal.y, -1.0, quat_eps) then -- The texture/decal needs to be flipped!
            q = q * quat(180.0, glm.forward())
        end
    end

    -- @NOTE RotationOrder 2 is ZXY, however, the YXZ angles are extracted
    local euler = vec3(glm.extractEulerAngleYXZ(q))
    return q,glm.deg(vec3(euler[2],euler[1],euler[3]))
end

--[[
    Example 3: Take the result to a raycast test and create a decal that is
    mapped to the surface normal.

    See "decalType" and "PatchDecalDiffuseMap" for its limitations.
--]]
function CreateDecalFromRaycastResult(decalType, pos, surface, entity, textureSize, m_quat)
    local decal_epsilon = 1E-2  -- Decal properties
    local decalTimeout = -1.0

    local decalForward = -surface
    local decalRight = nil
    if IsEntityAVehicle(entity) then
        -- If the raycast intersects a vehicle, align the forward vector of the
        -- vehicle to the 'right' vector of the decal.
        local forward,right,up,_ = GetEntityMatrix(entity)

        local dot_forward = dot(surface, forward)
        local dot_right = dot(surface, right)
        if glm.approx(glm.abs(dot_forward), 1.0, decal_epsilon) then
            decalRight = glm.sign(-dot_forward) * glm.projPlane(right, surface)
        elseif glm.approx(glm.abs(dot_right), 1.0, decal_epsilon) then
            decalRight = glm.sign(dot_right) * forward
        else
            decalRight = glm.projPlane(forward, surface)
        end
    else
        -- Slightly adjust the position of the decal relative to the surface to
        -- 'massage' texture mapping.
        pos = pos + surface * 0.05

        -- Compute a perpendicular of the surface
        decalRight = glm.perpendicular(surface, -glm.up(), glm.right())

        -- If the surface normal is upwards or downwards, rotate the Z (heading
        -- component) of the quaternion so any rendered texture/decal points
        -- towards the client camera.
        local dot_up = glm.dot(surface, glm.up())
        if glm.approx(glm.abs(dot_up), 1.0, decal_epsilon) then
            local camRot = GetFinalRenderedCamRot(2)
            decalRight = quat(camRot.z, glm.up()) * glm.right()
        end
    end

    return AddDecal(decalType,
        pos.x, pos.y, pos.z,
        decalForward.x, decalForward.y, decalForward.z,
        decalRight.x, decalRight.y, decalRight.z,
        textureSize.x, textureSize.y,
        1.0, 1.0, 1.0, 1.0,
        decalTimeout, 1, 0, 1 -- float timeout, BOOL p17, BOOL p18, allowOnVehicles
    )
end

--[[
    @TODO: After some pre-specified amount of time without the texture
    dictionary being loaded: throw an error
--]]
function LoadStreamedTextureDict(dict, texture)
    Citizen.Trace(("Loading Texture Dictionary: %s\n"):format(dict))

    RequestStreamedTextureDict(dict)
    while not HasStreamedTextureDictLoaded(dict) do
        Citizen.Wait(0)
    end

    Citizen.Trace(("Loaded Texture Dictionary: %s\n"):format(dict))
end

Citizen.CreateThread(function()
    local activeDict = "graffiti" -- Custom streamed textures
    local activeTexture = "Peace"
    local activeSize = vec2(5.0, 5.0)  -- The two dimensional size (prior to aspect adjustment) of the texture
    LoadStreamedTextureDict(activeDict, activeTexture)

    -- Adjust the 'size' of the texture according to its aspect ratio.
    local activeRes = GetTextureResolution(activeDict, activeTexture)
    local activeDims = vec2(activeSize.x * (activeRes.x / activeRes.y), activeSize.y)

    -- Create a decalType with the provided textures.
    local decalType = 10001 -- Starting index of 'unbound' decalType
    PatchDecalDiffuseMap(decalType, activeDict, activeTexture)

    local activeHandle = nil
    while true do
        Citizen.Wait(0)

        SetMouseCursorActiveThisFrame()
        local mx = GetDisabledControlNormal(0, 239)
        local my = GetDisabledControlNormal(0, 240)

        -- Create a ray from the camera origin that extends through the mouse cursor
        local r_pos,r_dir = ScreenPositionToCameraRay(mx, my)
        local b = r_pos + 10000 * r_dir

        -- StartExpensiveSynchronousShapeTestLosProbe
        local handle = StartShapeTestRay(r_pos.x,r_pos.y,r_pos.z, b.x,b.y,b.z, 1|2|8|16, PlayerPedId(), 7)

        local _,hit,pos,surface,entity = GetShapeTestResult(handle)
        if hit ~= 0 then -- Draw a preview using "DrawMarker":

            -- Slightly adjust the position of the marker so the texture does
            -- not clip with flat surfaces
            local m_pos = pos + surface * 0.25
            local _,m_euler = SurfaceNormalToMarkerRotation(surface)
            DrawMarker(
                9, -- int type,
                m_pos.x,m_pos.y,m_pos.z, -- float posX, float posY, float posZ,
                0.0, 0.0, 0.0, -- float dirX, float dirY, float dirZ,
                m_euler.x,m_euler.y,m_euler.z, -- float rotX, float rotY, float rotZ
                activeDims.x,activeDims.y,activeDims.y, -- float scaleX, float scaleY, float scaleZ,
                255,255,255,123, -- int red, int green, int blue, int alpha,
                false, -- BOOL bobUpAndDown
                false, -- BOOL faceCamera
                2, -- int rotationOrder
                false, -- BOOL rotate,
                activeDict, activeTexture, -- char* textureDict, char* textureName
                false --  BOOL drawOnEnts
            )

            -- Create a decal
            if IsControlJustReleased(0, 51) then -- ~INPUT_CONTEXT~
                if activeHandle ~= nil then
                    RemoveDecal(activeHandle)
                    activeHandle = nil
                end

                activeHandle = CreateDecalFromRaycastResult(decalType, pos,surface,entity, activeDims)
            end
        end
    end
end)
