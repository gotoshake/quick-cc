
local Levels = require("data.Levels")
local Coin   = require("views.Coin")
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

    --tmxMap
    self.map = CCTMXTiledMap:create("orthogonal-test4.tmx")
    self:addChild(self.map, 0, 10000)    

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

    --self.map:setAnchorPoint(ccp(0, 0))
    --self.map:setPosition(ccp(0, 0))

    self.layerFloor			= self.map:layerNamed("floor")
    self.layerFloorSize		= self.layerFloor:getLayerSize()
    
    self.layerTree			= self.map:layerNamed("tree")
    
    self.batch = display.newBatchNode(GAME_TEXTURE_IMAGE_FILENAME)
    --self.batch:setPosition(display.cx, display.cy)
    printf("setPosition: %f, %f", display.cx, display.cy)
    self.map:addChild(self.batch)    
    
    self.graph = {}    
    local  s1 = self.layerFloor:getLayerSize()
    self.tileColor = self.layerFloor:tileAt(ccp(0, 0)):getColor()  
    
    for j=0, s1.height-1 do    	
    	for i=0, s1.width-1 do    	    	
    		self.graph[j*s1.width + i] = {}    	
    		if  self.layerFloor:tileAt(ccp(i, s1.height-1-j)) then 
				self.graph[j*s1.width + i].weight = 1						
			end
			
			if  self.layerTree:tileAt(ccp(i, s1.height-1-j)) then 
				self.graph[j*s1.width + i].weight = math.huge						
			end    	
    	end    	
    end
    
    self.coins = {}
    
    local coin = Coin.new(1) 
    self.batch:addChild(coin, COIN_ZORDER)
    coin.board = self
    self.coins[1] =  coin

    local tilex, tiley = coin:getTilePos()    
    self.graph[tiley*s1.width + tilex].object = 1 

    self.maskLayer = display.newLayer()
    self:addChild(self.maskLayer)

    self:addTouchEventListener(handler(self, self.onTouch))
    self:setNodeEventEnabled(true)
end

function Board:screenToTilePos(x, y)
    local mapx, mapy = self.map:getPosition()
    local ts = self.map:getTileSize()
    return math.floor((x-mapx)/ts.width), math.floor((y-mapy)/ts.height)
end

function Board:setTileColor(x, y, color)	
	local tile = self.layerFloor:tileAt(ccp(x,  self.layerFloor:getLayerSize().height- 1-y))
	if tile then		
        local maskTile = CCSprite:create("mask.png")
        maskTile:setAnchorPoint(ccp(0, 0))
        maskTile:setPosition(tile:getPosition())
        self.maskLayer:addChild(maskTile, 0, 1)
	end
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
    self.maskLayer:removeAllChildrenWithCleanup()    
    
    local s1 = self.layerFloor:getLayerSize()
    

    if self.graph[tiley*s1.width+tilex] and self.graph[tiley*s1.width+tilex].object == 1  then
        self.coins[1].selected = 1
        self.paths, self.previous = dijkstra(self.graph , s1.width, s1.height, tilex, tiley, 5) 

        --echoInfo("------------")
        for i,j in pairs(self.paths) do
		  --print(i, j, table.concat(path(self.previous, i), ' -> '))
	    end
    
        for i,j in pairs(self.paths) do
		  local x = i%s1.width
		  local y = (i-x)/s1.width
		  self:setTileColor(x, y, ccc3(111, 111, 111))
        end
        
        return
	end
	
	if self.coins[1].selected and self.paths[tiley*s1.width+tilex] then        
        local coinPath = path(self.previous, tiley*s1.width+tilex)        
        self.coins[1].selected = nil
        self.coins[1]:moveTo(coinPath)
        self.graph[tiley*s1.width + tilex].object = 1 
    end
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
