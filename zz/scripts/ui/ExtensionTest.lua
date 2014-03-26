local TableViewTestLayer = class("TableViewTestLayer", function(mapIndex)   
    local map = CCLayer:create()     
    return map
end)

function TableViewTestLayer:ctor(roleIndex)
    self.__index = TableViewTestLayer
    local winSize = CCDirector:sharedDirector():getWinSize()

    local tableView = nil
    --[[
    tableView = CCTableView:create(CCSizeMake(600,60))
    tableView:setDirection(kCCScrollViewDirectionHorizontal)
    tableView:setPosition(CCPointMake(20, winSize.height / 2 - 150))
    self:addChild(tableView)
    --registerScriptHandler functions must be before the reloadData function
    tableView:registerScriptHandler(TableViewTestLayer.scrollViewDidScroll,CCTableView.kTableViewScroll)
    tableView:registerScriptHandler(TableViewTestLayer.scrollViewDidZoom,CCTableView.kTableViewZoom)
    tableView:registerScriptHandler(TableViewTestLayer.tableCellTouched,CCTableView.kTableCellTouched)
    tableView:registerScriptHandler(TableViewTestLayer.cellSizeForTable,CCTableView.kTableCellSizeForIndex)
    tableView:registerScriptHandler(TableViewTestLayer.tableCellAtIndex,CCTableView.kTableCellSizeAtIndex)
    tableView:registerScriptHandler(TableViewTestLayer.numberOfCellsInTableView,CCTableView.kNumberOfCellsInTableView)
    tableView:reloadData()
    ]]--

    tableView = CCTableView:create(CCSizeMake(60, 350))
    tableView:setDirection(kCCScrollViewDirectionVertical)
    tableView:setPosition(CCPointMake(winSize.width - 150, winSize.height / 2 - 150))
    tableView:setVerticalFillOrder(kCCTableViewFillTopDown)
    self:addChild(tableView)
    tableView:registerScriptHandler(TableViewTestLayer.scrollViewDidScroll,CCTableView.kTableViewScroll)
    tableView:registerScriptHandler(TableViewTestLayer.scrollViewDidZoom,CCTableView.kTableViewZoom)
    tableView:registerScriptHandler(TableViewTestLayer.tableCellTouched,CCTableView.kTableCellTouched)
    tableView:registerScriptHandler(TableViewTestLayer.cellSizeForTable,CCTableView.kTableCellSizeForIndex)
    tableView:registerScriptHandler(TableViewTestLayer.tableCellAtIndex,CCTableView.kTableCellSizeAtIndex)
    tableView:registerScriptHandler(TableViewTestLayer.numberOfCellsInTableView,CCTableView.kNumberOfCellsInTableView)
    tableView:reloadData()
    
    return true
end

--local TableViewTestLayer = class("TableViewTestLayer")
--TableViewTestLayer.__index = TableViewTestLayer

function TableViewTestLayer.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TableViewTestLayer)
    return target
end

function TableViewTestLayer.scrollViewDidScroll(view)
    --print("scrollViewDidScroll")
end

function TableViewTestLayer.scrollViewDidZoom(view)
    --print("scrollViewDidZoom")
end

function TableViewTestLayer.tableCellTouched(table,cell)
    print("cell touched at index: " .. cell:getIdx())
end

function TableViewTestLayer.cellSizeForTable(table,idx)
    return 60,120
end

function TableViewTestLayer.tableCellAtIndex(table, idx)
    local strValue = string.format("%d",idx)
    local cell = table:dequeueCell()
    local label = nil
    if nil == cell then
        cell = CCTableViewCell:new()
        local sprite = CCSprite:create("icon.png")
        sprite:setAnchorPoint(CCPointMake(0,0))
        sprite:setPosition(CCPointMake(0, 0))
        cell:addChild(sprite)

        label = CCLabelTTF:create(strValue, "Helvetica", 20.0)
        label:setPosition(CCPointMake(0,0))
        label:setAnchorPoint(CCPointMake(0,0))
        label:setTag(123)
        cell:addChild(label)
    else
        label = tolua.cast(cell:getChildByTag(123),"CCLabelTTF")
        if nil ~= label then
            label:setString(strValue)
        end
    end

    return cell
end

function TableViewTestLayer.numberOfCellsInTableView(table)
   return 25
end

return TableViewTestLayer
