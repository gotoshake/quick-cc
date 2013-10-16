local Levels = import("..data.Levels")
local RoleDatas = import("..data.RoleDatas")

local Coin = class("Coin", function(roleIndex)   
    --local RoleData = RoleDatas.get(roleIndex)
    --local sprite = display.newSprite("#" .. RoleData.name .. "_" .. RoleData.actionNames[1] .. "_01.png")  
    return display.newSprite()
end)

function Coin:ctor(roleIndex)
    self.roleIndex  = roleIndex
    self.map        = game.getMap()    
    self.data       = RoleDatas.get(roleIndex)

    self.direction  = "down"

    self:setAnchorPoint(ccp(0, 0))
    local spriteSize = game.getMap():getTileSize()    
    self:setPosition(ccp(self.data.pos.x *spriteSize.width, self.data.pos.y * spriteSize.height))
    self.map:setTileObject(self.data.pos.x+ self.data.pos.y*self.map.layerSize.width, self.roleIndex)  

    if display.getAnimationCache(self.data.resId .. RoleDatas.animations[1]) == nil then
        for  k, actionName in ipairs(RoleDatas.animations) do        
            local frames = display.newFrames(self.data.resId .. "_" .. RoleDatas.animations[k] .."_%02d.png", 1, RoleDatas.animationNums[k])
            display.setAnimationCache(self.data.resId .. actionName, display.newAnimation(frames, 0.15) )
        end          
    end 

   --self:playAnimationForever(display.getAnimationCache(self.data.resId .. RoleDatas.animations[1]))
end

function Coin:getTilePos()
    local s = game.getMap():getTileSize()
    local x, y = self:getPosition()
    return math.floor(x/s.width), math.floor(y/s.height)
end

function Coin:moveOver()    
end

function Coin:moveByStep()
    local currentTile = self.path[self.currentStep]
    local nextTile = self.path[self.currentStep+1]

    if nextTile then
        local spriteSize = game.getMap():getTileSize()
        local x, y = self:getPosition()
        local layerSize = self.map.layerSize

        if nextTile == currentTile- 1 then 
        	x = x-spriteSize.width
            local moveleft = CCSequence:createWithTwoActions(
                CCFlipX:create(false), 
                CCAnimate:create(display.getAnimationCache(self.data.resId .. "moveleft")))
                self:runAction(moveleft)  
        elseif nextTile == currentTile+ 1 then
        	x = x+spriteSize.width
            local moveright = CCSequence:createWithTwoActions(
                CCFlipX:create(true), 
                CCAnimate:create(display.getAnimationCache(self.data.resId .. "moveleft")))
            self:runAction(moveright)             
        elseif nextTile == currentTile- layerSize.width then
        	y = y-spriteSize.height
            self:playAnimationOnce(display.getAnimationCache(self.data.resId .. "movedown")) 
        elseif nextTile == currentTile+ layerSize.width then
        	y = y+spriteSize.height
            self:playAnimationOnce(display.getAnimationCache(self.data.resId .. "moveup"))        	
        end 
        
        self.currentStep = self.currentStep+1

        local action = CCSequence:createWithTwoActions(
                CCMoveTo:create(0.3, ccp(x, y)),
                CCCallFuncN:create(Coin.moveByStep))
        self:runAction(action)

    else
        self:moveOver()
        self:startIdleAnimation()
    end
end

function Coin:startIdleAnimation() 
    local action = CCRepeatForever:create(CCAnimate:create(display.getAnimationCache(self.data.resId .. "movedown")))
    action:setTag(1)
    self:runAction(action)  
end 

function Coin:stopIdleAnimation()  
    self:stopActionByTag(1)
end 

function Coin:attack() 
    if self.direction == "left" then           
            local moveleft = CCSequence:createWithTwoActions(
                CCFlipX:create(false), 
                CCAnimate:create(display.getAnimationCache(self.data.resId .. "attackleft")))
            self:runAction(moveleft)  
    elseif self.direction == "right" then            
            local moveright = CCSequence:createWithTwoActions(
                CCFlipX:create(true), 
                CCAnimate:create(display.getAnimationCache(self.data.resId .. "attackleft")))
            self:runAction(moveright)             
    elseif self.direction == "down" then
            self:playAnimationOnce(display.getAnimationCache(self.data.resId .. "attackdown")) 
    elseif self.direction == "up" then
            self:playAnimationOnce(display.getAnimationCache(self.data.resId .. "attackup"))          
    end 
end

function Coin:moveTo(path) 
    self:stopIdleAnimation()   
    print(table.concat(path, ' -> '))
    self.path = path
    self.currentStep = 1    
    self:moveByStep()

    self.map:setTileObject(self.path[1], 0)
    self.map:setTileObject(self.path[#self.path], self.roleIndex)
end

return Coin
