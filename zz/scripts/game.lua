
require("config")
require("framework.init")

-- define global module
game = {}

function game.startup()
    CCFileUtils:sharedFileUtils():addSearchPath("res/")    
    --display.addSpriteFramesWithFile("AllSprites.plist", "AllSprites.png")    
    display.addSpriteFramesWithFile(GAME_TEXTURE_DATA_FILENAME, GAME_TEXTURE_IMAGE_FILENAME)

    -- preload all sounds
    for k, v in pairs(GAME_SFX) do
        audio.preloadSound(v)
    end

    game.enterMenuScene()
end

function game.exit()
    CCDirector:sharedDirector():endToLua()
end

function game.enterMenuScene()
    display.replaceScene(require("scenes.MenuScene").new(), "fade", 0.6, display.COLOR_WHITE)
end

function game.enterMoreGamesScene()
    display.replaceScene(require("scenes.MoreGamesScene").new(), "fade", 0.6, display.COLOR_WHITE)
end

function game.enterChooseLevelScene()
    display.replaceScene(require("scenes.ChooseLevelScene").new(), "fade", 0.6, display.COLOR_WHITE)
end

function game.playLevel(levelIndex)
    game.PlayLevelScene = require("scenes.PlayLevelScene").new(levelIndex)
    display.replaceScene(game.PlayLevelScene, "fade", 0.6, display.COLOR_WHITE)
end

function game.getCoin(row)    
    return game.PlayLevelScene.board.coins[row]    
end

function game.getMap()
    return game.PlayLevelScene.board.map
end

function game.getMask()
    return game.PlayLevelScene.board.maskLayer
end

function game.getActionMenu()
    return game.PlayLevelScene.board.actionMenu
end


