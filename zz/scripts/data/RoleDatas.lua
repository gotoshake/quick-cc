local _RoleDatas = {}

_RoleDatas[1] = {
	resId = "1",
	pos = {x=0, y=0},
}

--_RoleDatas[2] = {
--	resId = "1",
--	pos = {x=3, y=0},  
--  
--}

local RoleDatas = {}

RoleDatas.animations = {"movedown", "moveup", "moveleft", "moveright", "injure", "attackdown", "attackup", "attackleft",  "attackright"}
RoleDatas.animationNums = {2, 2, 2, 2, 2, 4, 4, 4, 4}

RoleDatas.MOVE_DOWN 		= 1
RoleDatas.MOVE_UP 			= 2
RoleDatas.MOVE_LEFT 		= 3
RoleDatas.MOVE_RIGHT 		= 4
RoleDatas.INJURE 			= 5
RoleDatas.ATTACK_DOWN 		= 6
RoleDatas.ATTACK_UP 		= 7
RoleDatas.ATTACK_LEFT 		= 8
RoleDatas.ATTACK_RIGHT 		= 9



function RoleDatas.numRoles()
    return #_RoleDatas
end

function RoleDatas.get(roleIndex)
    assert(roleIndex >= 1 and roleIndex <= #_RoleDatas, string.format("RoleDatas.get() - invalid roleIndex %s", tostring(roleIndex)))
    return clone(_RoleDatas[roleIndex])
end

return RoleDatas