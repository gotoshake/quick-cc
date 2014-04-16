require("framework.functions")

require ("CharData")
require ("MapData")

local Char 	= require ("Char")
local Map 	= require ("Map")

Board = {}

function Board.init()

	Board.chars = {}
    for i=1, CharData.numChars() do
        local char = Char.new(CharData.get(i))
		Board.chars[i] = char
		print(char.data.name)
    end

	Board.map = Map.new()
end

function Board.getMap()
	return Board.map
end

function Board.getchar(index)
	assert(index >= 1 and index <= #Board.chars, string.format("Board.getchar - invalid index %s", tostring(index)))
    return Board.chars[i]
end

