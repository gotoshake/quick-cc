local Levels = import("..data.Levels")
local RoleDatas = import("..data.RoleDatas")

local Coin = class("Coin", function(roleIndex)   
    --local RoleData = RoleDatas.get(roleIndex)
    --local sprite = display.newSprite("#" .. RoleData.name .. "_" .. RoleData.actionNames[1] .. "_01.png")  
    return display.newSprite()
end)

function Coin:tilePosToRealPos(tilex, tiley)
    local s = game.getMap():getTileSize()
    return ccp(tilex* s.width, tiley* s.height)
end

function Coin:ctor(roleIndex)
    self.roleIndex  = roleIndex
    self.map        = game.getMap()    
    local RoleData  = RoleDatas.get(roleIndex)

    self:setAnchorPoint(ccp(0, 0))
    local spriteSize = game.getMap():getTileSize()    
    self:setPosition(ccp(RoleData.pos.x *spriteSize.width, RoleData.pos.y * spriteSize.height))
    self.map:setTileObject(RoleData.pos.x+ RoleData.pos.y*self.map.layerSize.width, self.roleIndex)  

    for  k, actionName in ipairs(RoleData.actionNames) do        
        local frames = display.newFrames(RoleData.name .. "_" .. RoleData.actionNames[k] .."_%02d.png", 1, RoleData.actionNums[k])
        display.setAnimationCache(roleIndex .. actionName, display.newAnimation(frames, 0.15) )           
    end 

    self.batch = display.newBatchNode(GAME_TEXTURE_IMAGE_FILENAME)
    self:playAnimationOnce(display.getAnimationCache(roleIndex .. "moveup"))  
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
                CCAnimate:create(display.getAnimationCache(self.roleIndex .. "moveleft")))
                self:runAction(moveleft)  
        elseif nextTile == currentTile+ 1 then
        	x = x+spriteSize.width
            local moveright = CCSequence:createWithTwoActions(
                CCFlipX:create(true), 
                CCAnimate:create(display.getAnimationCache(self.roleIndex .. "moveleft")))
            self:runAction(moveright)             
        elseif nextTile == currentTile- layerSize.width then
        	y = y-spriteSize.height
            self:playAnimationOnce(display.getAnimationCache(self.roleIndex .. "movedown")) 
        elseif nextTile == currentTile+ layerSize.width then
        	y = y+spriteSize.height
            self:playAnimationOnce(display.getAnimationCache(self.roleIndex .. "moveup"))        	
        end 
        
        self.currentStep = self.currentStep+1

        local action = CCSequence:createWithTwoActions(
                CCMoveTo:create(0.3, ccp(x, y)),
                CCCallFuncN:create(Coin.moveByStep))
        self:runAction(action)

    else
        self:moveOver()
    end
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
