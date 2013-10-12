
local Levels = import("..data.Levels")
local Board = import("..views.Board")

local PlayLevelScene = class("PlayLevelScene", function()
    return display.newScene("PlayLevelScene")
end)

function PlayLevelScene:ctor(levelIndex) 
    -- create board   
    self.board = Board.new(Levels.get(levelIndex))
    self.board:addEventListener("LEVEL_COMPLETED", handler(self, self.onLevelCompleted))
    self:addChild(self.board)

    -- create levels list
    --local rect = CCRect(display.left, display.bottom + 180, display.width, display.height - 280)
    --self.levelsList = require("views.LevelsList").new(rect)
    --self.levelsList:addEventListener("onTapLevelIcon", handler(self, self.onTapLevelIcon))
    --self:addChild(self.levelsList)

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

function PlayLevelScene:onTapLevelIcon(event)
    audio.playSound(GAME_SFX.tapButton)
    game.playLevel(event.levelIndex)
end

function PlayLevelScene:onEnter()
    --self.levelsList:setTouchEnabled(true)
end

return PlayLevelScene
