local Levels = import("..data.Levels")
local RoleDatas = import("..data.RoleDatas")

local Coin = class("Coin", function(roleIndex)   
    local RoleData = RoleDatas.get(roleIndex)
    local sprite = display.newSprite("#" .. RoleData.name .. "_" .. RoleData.actionNames[1] .. "_01.png")       
    return sprite
end)

function Coin:tilePosToRealPos(tilex, tiley)
    local s = self:getContentSize()
    return ccp(tilex* s.width, tiley* s.height)
end

function Coin:ctor(roleIndex)
    self.animations = {}
    local frames

    local RoleData = RoleDatas.get(roleIndex)

    self:setAnchorPoint(ccp(0, 0))
    local spriteSize = self:getContentSize()
    self:setPosition(ccp(RoleData.pos.x *spriteSize.width, RoleData.pos.y * spriteSize.height))

    for  k, actionName in ipairs(RoleData.actionNames) do        
        frames = display.newFrames(RoleData.name .. "_" .. RoleData.actionNames[k] .."_%02d.png", 1, RoleData.actionNums[k])
        self.animations[actionName] = display.newAnimation(frames, 0.2)

        if  string.find(actionName, "left") then
            frames = display.newFrames(RoleData.name .. "_" .. RoleData.actionNames[k] .."_%02d.png", 1, RoleData.actionNums[k], true)
            self.animations[string.gsub(actionName, "left", "right")] = display.newAnimation(frames, 0.2)
        end    
    end

    self:playAnimationForever(self.animations["moveleft"]) 
end

function Coin:getTilePos()
    local s = self:getContentSize()
    local x, y = self:getPosition()
    return math.floor(x/s.width), math.floor(y/s.height)
end

function Coin:moveLeft()
    self:playAnimationForever(self.animations["moveleft"]) 
end

function Coin:moveRight()
    self:playAnimationForever(self.animations["moveright"]) 
end

function Coin:moveUp()
    self:playAnimationForever(self.animations["moveup"]) 
end

function Coin:moveDown()
    self:playAnimationForever(self.animations["movedown"]) 
end

return Coin
