local Map = class("Map", function(mapIndex)   
    local map = CCTMXTiledMap:create("orthogonal-test4.tmx")     
    return map
end)

function Map:ctor(mapIndex)
    local  pChildrenArray = self:getChildren()
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

    self.layerFloor         = self:layerNamed("floor")
    self.layerSize          = self.layerFloor:getLayerSize()

    self.tileSize           = self:getTileSize()
    
    self.layerTree          = self:layerNamed("tree")
    
    self.graph = {}    
    local  s1 = self.layerFloor:getLayerSize()
    self.tileColor = self.layerFloor:tileAt(ccp(0, 0)):getColor()  
    
    for j=0, s1.height-1 do     
        for i=0, s1.width-1 do              
            self.graph[j*s1.width + i] = {}
            self.graph[j*s1.width + i].object = 0    
            if  self.layerFloor:tileAt(ccp(i, s1.height-1-j)) then 
                self.graph[j*s1.width + i].weight = 1                       
            end
            
            if  self.layerTree:tileAt(ccp(i, s1.height-1-j)) then 
                self.graph[j*s1.width + i].weight = math.huge                       
            end     
        end     
    end    
end

function Map:setTileColor(tilex, tiley, color)    
    local tile = self.layerFloor:tileAt(ccp(tilex,  self.layerFloor:getLayerSize().height- 1-tiley))
    if tile then        
        local maskTile = CCSprite:create("mask.png")
        maskTile:setAnchorPoint(ccp(0, 0))
        maskTile:setPosition(tile:getPosition())
        game.getMask():addChild(maskTile, 1)
    end
end

function Map:setTileObject(tile, objectId)
    self.graph[tile].object = objectId
end

function Map:onTileTouched(tilex, tiley)
    if tilex<0 or tilex>self.layerSize.width-1 or tiley<0 or tiley>self.layerSize.height-1 then
        return
    end

    game.getMask():removeAllChildrenWithCleanup() 
    
    local s1 = self.layerFloor:getLayerSize()
    local tileObject = self.graph[tiley*s1.width+tilex].object

    if self.selected == nil and tileObject >0 then
        self.selected = tileObject
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

    if self.selected then        
        if self.paths[tiley*s1.width+tilex] and tileObject == 0 then        
            local coinPath = path(self.previous, tiley*s1.width+tilex)
            game.getCoin(self.selected):moveTo(coinPath)
        end 
        self.selected = nil      
    end
end

return Map