local ActionMenu = class("ActionMenu", function()
    local blockSize = CCSizeMake(128, 70)    
    local colorLayer = CCLayerColor:create(ccc4(100, 100, 100, 255), blockSize.width, blockSize.height)
    colorLayer:setAnchorPoint(ccp(0,0))
    return colorLayer
end)

function ActionMenu:ctor()
    self:setPosition(ccp(display.width-128, 0))
	-- create menu
    self.attack = ui.newTTFLabelMenuItem({
        text = "attack",        
        size = 32,
        x = 0,
        y = 0,       
        align = ui.TEXT_ALIGN_CENTER,
        listener = function()             
        end,
    })

    self.standby = ui.newTTFLabelMenuItem({
        text = "standby",        
        size = 32,
        x = 0,
        y = 32,  
        align = ui.TEXT_ALIGN_CENTER,
        listener = function()                   
        end,
    })

    self.attack:setAnchorPoint(ccp(0,0))
    self.standby:setAnchorPoint(ccp(0,0))

    self.menu = ui.newMenu({self.attack, self.standby})
    self:addChild(self.menu)
end

function ActionMenu:show()
    self:setVisible(true)
end

function ActionMenu:show()
    self:setVisible(true)    
end

return ActionMenu
