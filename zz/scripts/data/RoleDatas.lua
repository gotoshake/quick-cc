local _RoleDatas = {}

_RoleDatas[1] = {
	resId = "1",
	pos = {x=1, y=1},
}

--_RoleDatas[2] = {
--	resId = "1",
--	pos = {x=3, y=0},  
--  
--}

local RoleDatas = {}

RoleDatas.animations = {"movedown", "moveup", "moveleft", "injure", "attackdown", "attackup", "attackleft"}
RoleDatas.animationNums = {2, 2, 2, 2, 4, 4, 4}

function RoleDatas.numRoles()
    return #_RoleDatas
end

function RoleDatas.get(roleIndex)
    assert(roleIndex >= 1 and roleIndex <= #_RoleDatas, string.format("RoleDatas.get() - invalid roleIndex %s", tostring(roleIndex)))
    return clone(_RoleDatas[roleIndex])
end

return RoleDatas