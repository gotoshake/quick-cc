local RoleDatas = {}

function RoleDatas.numRoles()
    return #_RoleDatas
end

function RoleDatas.get(roleIndex)
    assert(roleIndex >= 1 and roleIndex <= #_RoleDatas, string.format("RoleDatas.get() - invalid roleIndex %s", tostring(roleIndex)))
    return clone(_RoleDatas[roleIndex])
end

local _RoleDatas = {}

_rolesData[1] = {
	roleName = "zhaoyun"
	rolePos = {x=0, y=0}    
    actionNames = {"dance_a_1", "dance_a_2", "stand_1", "stand_2", "walk_1", "walk_2"}
    actionNums = {8, 8, 4, 4, 8, 8}
}

return RoleDatas