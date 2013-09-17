
local Levels = {}

Levels.NODE_IS_WHITE  = 1
Levels.NODE_IS_BLACK  = 0
Levels.NODE_IS_EMPTY  = "X"

local levelsData = {}

levelsData[1] = {
    rows = 4,
    cols = 4,
    grid = {
        {1, 1, 1, 1},
        {1, 1, 0, 1},
        {1, 0, 0, 0},
        {1, 1, 0, 1}
    }
}

levelsData[2] = {
    rows = 4,
    cols = 4,
    grid = {
        {1, 0, 1, 1},
        {0, 0, 1, 1},
        {1, 1, 0, 0},
        {1, 1, 0, 1}
    }
}

levelsData[3] = {
    rows = 4,
    cols = 4,
    grid = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    }
}

levelsData[4] = {
    rows = 4,
    cols = 4,
    grid = {
        {0, 1, 1, 1},
        {1, 0, 0, 1},
        {1, 0, 1, 1},
        {1, 1, 1, 1}
    }
}

levelsData[5] = {
    rows = 4,
    cols = 4,
    grid = {
        {1, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 0, 0, 1}
    }
}

levelsData[6] = {
    rows = 4,
    cols = 4,
    grid = {
        {1, 0, 0, 1},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {1, 0, 0, 1}
    }
}



function Levels.numLevels()
    return #levelsData
end

function Levels.get(levelIndex)
    assert(levelIndex >= 1 and levelIndex <= #levelsData, string.format("levelsData.get() - invalid levelIndex %s", tostring(levelIndex)))
    return clone(levelsData[levelIndex])
end

return Levels
