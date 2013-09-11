local _RoleDatas = {}

_RoleDatas[1] = {
	name = "zhaoyun",
	pos = {x=0, y=0},    
    actionNames = {"movedown", "moveup", "moveleft"},
    actionNums = {2, 2, 2}
}

local RoleDatas = {}

function RoleDatas.numRoles()
    return #_RoleDatas
end

function RoleDatas.get(roleIndex)
    assert(roleIndex >= 1 and roleIndex <= #_RoleDatas, string.format("RoleDatas.get() - invalid roleIndex %s", tostring(roleIndex)))
    return clone(_RoleDatas[roleIndex])
end

return RoleDatas