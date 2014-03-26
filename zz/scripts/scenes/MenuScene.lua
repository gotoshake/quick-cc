
local MenuScene = class("MenuScene", function()
    return display.newScene("MenuScene")
end)

function MenuScene:ctor()
    -- create menu
    self.startButton = ui.newTTFLabelMenuItem({
        text = "ST",
        size = 32,
        x = display.width/2,
        y = display.bottom + 200,
        align = ui.TEXT_ALIGN_CENTER,
        sound = GAME_SFX.tapButton,
        prepare = function()
            self.menu:setEnabled(false)
            self.layer:setKeypadEnabled(false)
        end,
        listener = function()
            game.playLevel(1)
        end,
    }) 

    self.endButton = ui.newTTFLabelMenuItem({
        text = "ED",
        size = 32,
        x = display.width/2,
        y = display.bottom + 150,
        align = ui.TEXT_ALIGN_CENTER,
        sound = GAME_SFX.tapButton,
        prepare = function()
            self.menu:setEnabled(false)
            self.layer:setKeypadEnabled(false)
        end,
        listener = function()
            game.exit()
        end,
    }) 

    self.menu = ui.newMenu({self.endButton, self.startButton})
    self:addChild(self.menu)

    -- keypad layer, for android
    self.layer = display.newLayer()
    self.layer:addKeypadEventListener(function(event)
        if event == "back" then
            audio.playSound(GAME_SFX.backButton)
            game.exit()
        end
    end)
    self:addChild(self.layer)
end

function MenuScene:onEnter()
    -- avoid unmeant back
    self:performWithDelay(function()
        self.layer:setKeypadEnabled(true)
    end, 0.5)

    game.playLevel(1)
end

return MenuScene
