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

    self.direction  = RoleDatas.DIRECTION_DOWN
    self.animeId    = 0

    self:setAnchorPoint(ccp(0, 0))
    local spriteSize = game.getMap():getTileSize()    
    self:setPosition(ccp(self.data.pos.x *spriteSize.width, self.data.pos.y * spriteSize.height))
    self.map:setTileObject(self.data.pos.x+ self.data.pos.y*self.map.layerSize.width, self.roleIndex)  

    if display.getAnimationCache(self.data.resId .. RoleDatas.animations[1]) == nil then
        for  k, actionName in ipairs(RoleDatas.animations) do
            if (string.find(actionName, "right") == nil) then
                local frames = display.newFrames(self.data.resId .. "_" .. RoleDatas.animations[k] .."_%02d.png", 1, RoleDatas.animationNums[k])
                display.setAnimationCache(self.data.resId .. actionName, display.newAnimation(frames, 0.3) )
            end
        end          
    end 

    self:startAnimation(RoleDatas.MOVE_DOWN, 1)
end

function Coin:getTilePos()
    local s = game.getMap():getTileSize()
    local x, y = self:getPosition()
    return math.floor(x/s.width), math.floor(y/s.height)
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
            --self:startAnimation(RoleDatas.MOVE_LEFT, 1)
            self.direction = RoleDatas.DIRECTION_LEFT
        elseif nextTile == currentTile+ 1 then
        	x = x+spriteSize.width
            --self:startAnimation(RoleDatas.MOVE_RIGHT, 1)
            self.direction = RoleDatas.DIRECTION_RIGHT           
        elseif nextTile == currentTile- layerSize.width then
        	y = y-spriteSize.height
            --self:startAnimation(RoleDatas.MOVE_DOWN, 1)
            self.direction = RoleDatas.DIRECTION_DOWN  
        elseif nextTile == currentTile+ layerSize.width then
        	y = y+spriteSize.height
            --self:startAnimation(RoleDatas.MOVE_UP, 1)
            self.direction = RoleDatas.DIRECTION_UP          	
        end
                
        self:startAnimation(RoleDatas.MOVE_DOWN +self.direction -1, 1) 
        
        self.currentStep = self.currentStep+1

        local action = CCSequence:createWithTwoActions(
                CCMoveTo:create(0.2, ccp(x, y)),
                CCCallFuncN:create(Coin.moveByStep))
        self:runAction(action)

    else
        --echoInfo("moveOver")      
    end
end

function Coin:startAnimation(animeId, bForever, callBack)        
    if self.animeId == 0 or self.animeId ~= animeId then 

        if self.animeId ~= 0 then
            self:stopActionByTag(self.animeId)
        end

        local arr = CCArray:create()
        if string.find(RoleDatas.animations[animeId], "right") == nil then
            arr:addObject(CCFlipX:create(false)) 
            arr:addObject(CCAnimate:create(display.getAnimationCache(self.data.resId .. RoleDatas.animations[animeId])))
        else
            arr:addObject(CCFlipX:create(true)) 
            arr:addObject(CCAnimate:create(display.getAnimationCache(self.data.resId .. RoleDatas.animations[animeId-1])))
        end

        if callBack then
            arr:addObject(CCCallFuncN:create(callBack))
        end

        local action
        if bForever == 1 then
            action = CCRepeatForever:create(CCSequence:create(arr))
        else
            action = CCSequence:create(arr) 
        end
        action:setTag(animeId)
        self.animeId = animeId
        self:runAction(action) 
    end 
end 

function Coin:stopAnimation()  
    self:stopActionByTag(self.animeId)
end 

function Coin:attack(direction)    
        self:startAnimation(RoleDatas.ATTACK_DOWN +direction -1, 0, Coin.attackOver)
end

function Coin:attackOver()
    echoInfo("attackOver")
end

function Coin:moveTo(path)    
    print(table.concat(path, ' -> '))
    self.path = path
    self.currentStep = 1    
    self:moveByStep()

    self.map:setTileObject(self.path[1], 0)
    self.map:setTileObject(self.path[#self.path], self.roleIndex)
end

return Coin
