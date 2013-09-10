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
    local RoleData = RoleDatas.get(roleIndex)

    self:setAnchorPoint(ccp(0, 0))
    local spriteSize = self:getContentSize()
    self:setPosition(ccp(RoleData.pos.x *spriteSize.width, RoleData.pos.y * spriteSize.height))

    for  k, actionName in ipairs(RoleData.actionNames) do        
        local frames = display.newFrames(RoleData.name .. "_" .. RoleData.actionNames[k] .."_%02d.png", 1, RoleData.actionNums[k])
        display.setAnimationCache(actionName, display.newAnimation(frames, 0.15) )           
    end    
end

function Coin:getTilePos()
    local s = self:getContentSize()
    local x, y = self:getPosition()
    return math.floor(x/s.width), math.floor(y/s.height)
end

function Coin:moveByStep()    
    local currentTile = self.path[self.currentStep]
    local nextTile = self.path[self.currentStep+1]

    if nextTile then
        local spriteSize = self:getContentSize()
        local x, y = self:getPosition()
        local layerSize = self.board.layerFloorSize
         

        if nextTile == currentTile- 1 then 
        	x = x-spriteSize.width
            local moveleft = CCSequence:createWithTwoActions(
                CCFlipX:create(false), 
                CCAnimate:create(display.getAnimationCache("moveleft")))
                self:runAction(moveleft)  
        elseif nextTile == currentTile+ 1 then
        	x = x+spriteSize.width
            local moveright = CCSequence:createWithTwoActions(
                CCFlipX:create(true), 
                CCAnimate:create(display.getAnimationCache("moveleft")))
            self:runAction(moveright)             
        elseif nextTile == currentTile- layerSize.width then
        	y = y-spriteSize.height
            self:playAnimationOnce(display.getAnimationCache("movedown")) 
        elseif nextTile == currentTile+ layerSize.width then
        	y = y+spriteSize.height
            self:playAnimationOnce(display.getAnimationCache("moveup"))        	
        end        

        self.board.graph[currentTile].object = 0
        self.board.graph[nextTile].object = 1
        
        self.currentStep = self.currentStep+1

        local action = CCSequence:createWithTwoActions(
                CCMoveTo:create(0.3, ccp(x, y)),
                CCCallFuncN:create(Coin.moveByStep))
        self:runAction(action)
    end
end

function Coin:moveTo(path)    
    print(table.concat(path, ' -> '))
    self.path = path
    self.currentStep = 1
    self:moveByStep()
end

return Coin
