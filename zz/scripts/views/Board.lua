
local Levels = require("data.Levels")
local Coin   = require("views.Coin")
local EventProtocol = require("framework.api.EventProtocol")

local Board = class("Board", function()
    return display.newLayer()
end)

local NODE_PADDING   = 100
local NODE_ZORDER    = 0
local COIN_ZORDER    = 1000

function Board:ctor(levelData)
    EventProtocol.extend(self)

    self.label = ui.newBMFontLabel({
        text  = string.format("Level: %s", tostring(levelIndex)),
        font  = "UIFont.fnt",
        x     = display.left + 10,
        y     = display.top - 30,
        align = ui.TEXT_ALIGN_LEFT,
    })
    self:addChild(self.label)

    --tmxMap
    self.map = CCTMXTiledMap:create("orthogonal-test4.tmx")
    self:addChild(self.map, 0, 10000)

    local  s1 = self.map:getContentSize()
    --printf("ContentSize: %f, %f", s1.width,s1.height)

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
    self.map:setPosition(ccp(100, 50))

    local layer  = self.map:layerNamed("tree")
    local s      = layer:getLayerSize()


    self.batch = display.newBatchNode(GAME_TEXTURE_IMAGE_FILENAME)
    --self.batch:setPosition(display.cx, display.cy)
    printf("setPosition: %f, %f", display.cx, display.cy)
    self.map:addChild(self.batch)

    self.grid = clone(levelData.grid)
    self.rows = 0
    self.cols = 0
    self.coins = {}

    local coin = Coin.new(1) 
    self.batch:addChild(coin, COIN_ZORDER)
    coin.mapLayer = this       

    self:addTouchEventListener(handler(self, self.onTouch))
    self:setNodeEventEnabled(true)
end

function Board:screenToTilePos(x, y)
    local mapx, mapy = self.map:getPosition()
    local ts = self.map:getTileSize()
    return (x-mapx)/ts.width, (y-mapy)/ts.height
end

function Board:checkLevelCompleted()
    local count = 0
    for _, coin in ipairs(self.coins) do
        if coin.isWhite then count = count + 1 end
    end
    if count == #self.coins then
        -- completed
        self:setTouchEnabled(false)
        self:dispatchEvent({name = "LEVEL_COMPLETED"})
    end
end

function Board:getCoin(row, col)
    if self.grid[row] then
        return self.grid[row][col]
    end
end

function Board:onTouchBegan(x, y)
    local tilex,tiley = self:screenToTilePos(x, y)    
    self.label:setString(string.format("onTouchBegan %d %d -> %d %d", x, y, tilex, tiley))
end

function Board:onTouchMoved(x, y)
    echoInfo("onTouchMoved %d %d", x, y)    
end

function Board:onTouchEnded(x, y)   
    echoInfo("onTouchEnded %d %d", x, y)
end

function Board:onTouchCancelled(x, y)
    echoInfo("onTouchCancelled %d %d", x, y)
end

function Board:onTouch(event, x, y)
    if event == "began" then
        self:onTouchBegan(x, y)
    elseif event == "moved" then
        self:onTouchMoved(x, y)
    elseif event == "ended" then
        self:onTouchEnded(x, y)
    else -- cancelled
        self:onTouchCancelled(x, y)
    end
end

function Board:onEnter()
    self:setTouchEnabled(true)
end

function Board:onExit()
    self:removeAllEventListeners()
end

return Board
