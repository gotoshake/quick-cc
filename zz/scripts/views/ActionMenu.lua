local ActionMenu = class("ActionMenu", function()
    return display.newSprite()
end)

function ActionMenu:ctor()

    self:setColor(ccc3(255, 255, 0))
    self:setTextureRect(CCRectMake(0, 0, 120, 50))

    self:setPosition(ccp(display.width/2, display.height/2))
	-- create menu
    self.attack = ui.newTTFLabelMenuItem({
        text = "attack",        
        size = 32,        
        --align = ui.TEXT_ALIGN_CENTER,
        listener = function() 
            print("11")           
        end,
    })

    self.standby = ui.newTTFLabelMenuItem({
        text = "standby",        
        size = 32,
        --align = ui.TEXT_ALIGN_CENTER,
        listener = function()            
        end,
    })

    self.menu = ui.newMenu({self.attack, self.standby})
    self:addChild(self.menu)
end

return ActionMenu
