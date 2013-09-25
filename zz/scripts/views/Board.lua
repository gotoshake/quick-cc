
local Levels = require("data.Levels")
local Coin   = require("views.Coin")
local Map    = require("views.Map")
local ActionMenu    = require("views.ActionMenu")
import("..path.dijkstra")

local EventProtocol = require("framework.api.EventProtocol")

local Board = class("Board", function()
    return display.newLayer()
end)

local NODE_PADDING   = 100
local NODE_ZORDER    = 0
local COIN_ZORDER    = 1000

function Board:ctor(levelData)
    EventProtocol.extend(self)

    self.label = ui.newTTFLabel({        
        x     = display.left + 100,
        y     = display.top - 30,
    })
    self:addChild(self.label)

    --ui
    self.actionMenu = ActionMenu.new()
    self:addChild(self.actionMenu)
    
    --tmxMap
    self.map = Map.new(1) 
    --self:addChild(self.map, 0, 10000)     

    --self:addTouchEventListener(handler(self, self.onTouch))
    self:setNodeEventEnabled(true)
end

function Board:screenToTilePos(x, y)
    local mapx, mapy = self.map:getPosition()
    local ts = self.map:getTileSize()
    return math.floor((x-mapx)/ts.width), math.floor((y-mapy)/ts.height)
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
    self.label:setString(string.format("%d %d -> %d %d", x, y, tilex, tiley)) 
    self.map:onTileTouched(tilex, tiley)
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
