
local Levels = import("..data.Levels")
local Board = import("..views.Board")

local PlayLevelScene = class("PlayLevelScene", function()
    return display.newScene("PlayLevelScene")
end)

function PlayLevelScene:ctor(levelIndex)    

    local label = ui.newBMFontLabel({
        text  = string.format("Level: %s", tostring(levelIndex)),
        font  = "UIFont.fnt",
        x     = display.left + 10,
        y     = display.top - 30,
        align = ui.TEXT_ALIGN_LEFT,
    })
    self:addChild(label)

    self.board = Board.new(Levels.get(levelIndex))
    self.board:addEventListener("LEVEL_COMPLETED", handler(self, self.onLevelCompleted))
    self:addChild(self.board)

    -- create menu
    local backButton = ui.newTTFLabelMenuItem({
        text = "Back",        
        size = 32,
        x = display.right - 100,
        y = display.top - 30,
        align = ui.TEXT_ALIGN_CENTER,
        sound = GAME_SFX.backButton,       
        listener = function()
            game.enterMenuScene()
        end,
    }) 

    local menu = ui.newMenu({backButton})
    self:addChild(menu)
end

function PlayLevelScene:onLevelCompleted()
    audio.playEffect(GAME_SFX.levelCompleted)

    local dialog = display.newSprite("#LevelCompletedDialogBg.png")
    dialog:setPosition(display.cx, display.top + dialog:getContentSize().height / 2 + 40)
    self:addChild(dialog)

    transition.moveTo(dialog, {time = 0.7, y = display.top - dialog:getContentSize().height / 2 - 40, easing = "BOUNCEOUT"})
end

function PlayLevelScene:onEnter()
end

return PlayLevelScene
