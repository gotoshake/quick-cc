
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

    --tmxMap
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


    self.batch = display.newBatchNode(GAME_TEXTURE_IMAGE_FILENAME)
    self.batch:setPosition(display.cx, display.cy)
    self:addChild(self.batch)

    self.grid = clone(levelData.grid)
    self.rows = 0
    self.cols = 0
    self.coins = {}

    local coin = Coin.new(1)
    coin:setPosition(0, 0)
    coin.row = row
    coin.col = col
    --self.grid[row][col] = coin
    --self.coins[#self.coins + 1] = coin
    self.batch:addChild(coin, COIN_ZORDER)
          

    self:addTouchEventListener(handler(self, self.onTouch))
    self:setNodeEventEnabled(true)
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

function Board:flipCoin(coin, includeNeighbour)
    if not coin or coin == Levels.NODE_IS_EMPTY then return end

    self.flipAnimationCount = self.flipAnimationCount + 1
    coin:flip(function()
        self.flipAnimationCount = self.flipAnimationCount - 1
        self.batch:reorderChild(coin, COIN_ZORDER)
        if self.flipAnimationCount == 0 then
            self:checkLevelCompleted()
        end
    end)
    if includeNeighbour then
        audio.playEffect(GAME_SFX.flipCoin)
        self.batch:reorderChild(coin, COIN_ZORDER + 1)
        self:performWithDelay(function()
            self:flipCoin(self:getCoin(coin.row - 1, coin.col))
            self:flipCoin(self:getCoin(coin.row + 1, coin.col))
            self:flipCoin(self:getCoin(coin.row, coin.col - 1))
            self:flipCoin(self:getCoin(coin.row, coin.col + 1))
        end, 0.25)
    end
end

function Board:onTouch(event, x, y)
    if event ~= "began" or self.flipAnimationCount > 0 then return end

    local padding = NODE_PADDING / 2
    for _, coin in ipairs(self.coins) do
        local cx, cy = coin:getPosition()
        cx = cx + display.cx
        cy = cy + display.cy
        if x >= cx - padding
            and x <= cx + padding
            and y >= cy - padding
            and y <= cy + padding then
            self:flipCoin(coin, true)
            break
        end
    end
end

function Board:onEnter()
    self:setTouchEnabled(true)
end

function Board:onExit()
    self:removeAllEventListeners()
end

return Board
