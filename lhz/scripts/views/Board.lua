
local Board = class("Board", function()
    return display.newLayer()
end)

function Board:ctor(nlevel)
    self.map = CCTMXTiledMap:create("orthogonal-test4.tmx")
    self:addChild(self.map, 0, 10000)

    local  s1 = self.map:getContentSize()
    print("ContentSize: %f, %f", s1.width,s1.height)

    local  pChildrenArray = self.map:getChildren()
    local  child          = nil
    local  pObject        = nil
    local  i              = 0
    local  len            = pChildrenArray:count()

    for i = 0, len-1, 1 do
        child = tolua.cast(pChildrenArray:objectAtIndex(i), "CCSpriteBatchNode")

        if child == nil then
            break
        end
        child:getTexture():setAntiAliasTexParameters()
    end

    self.map:setAnchorPoint(ccp(0, 0))

    local layer  = self.map:layerNamed("Layer 0")
    local s      = layer:getLayerSize()
   

    self:addTouchEventListener(handler(self, self.onTouch))
    self:setNodeEventEnabled(true)
end

function Board:onTouch(event, x, y)
    if event ~= "began" then return end    
end

function Board:onEnter()
    self:setTouchEnabled(true)
end

function Board:onExit()
end

return Board
