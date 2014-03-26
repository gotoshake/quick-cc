
local Levels = require("data.Levels")
local Coin   = require("views.Coin")
local Map    = require("views.Map")
local ActionMenu    = require("views.ActionMenu")

require("path.dijkstra")
require("data.RoleDatas")
local tvTestLayer  =require("ui.ExtensionTest")

local EventProtocol = require("framework.api.EventProtocol")

local Board = class("Board", function()
    return display.newLayer()
end)

function Board:ctor(levelData)
    EventProtocol.extend(self)
    self:addTouchEventListener(handler(self, self.onTouch))
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
    --echoInfo("onTouch %s %d %d", event, x, y)
    if event == "began" then
        --self:onTouchBegan(x, y)
    elseif event == "moved" then
        self:onTouchMoved(x, y)
    elseif event == "ended" then
        self:onTouchEnded(x, y)
    else -- cancelled
        self:onTouchCancelled(x, y)
    end
end

function Board:onEnter()
    self.label = ui.newTTFLabel({        
        x     = display.left + 100,
        y     = display.top - 30,
    })
    --self:addChild(self.label)

    --ui
    self.actionMenu = ActionMenu.new()
    --self:addChild(self.actionMenu, 1)
    
    --tmxMap
    self.map = Map.new(1) 
    --self:addChild(self.map, 0)
    self:setTouchEnabled(true)

    --role
    --self.batch = display.newBatchNode(GAME_TEXTURE_IMAGE_FILENAME)
    --self.batch:setPosition(display.cx, display.cy)
    --printf("setPosition: %f, %f", display.cx, display.cy)
    --self:addChild(self.batch) 

    self.coins = {}
    for i=1, RoleDatas.numRoles() do    
        local coin = Coin.new(i) 
        --self:addChild(coin, 1000)  
        self.coins[i] =  coin
    end

    --mask    
    self.maskLayer = display.newSprite()
    self:addChild(self.maskLayer, 10)

    --table view
    self.tableView = tvTestLayer.new(0)
    self:addChild(self.tableView, 11)
end

function Board:onExit()
    self:removeAllEventListeners()
end

return Board
