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
    --self:addChild(label)

    self.board = Board.new(levelIndex)
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
    game.enterMenuScene()    
end

function PlayLevelScene:onEnter()
end

return PlayLevelScene
