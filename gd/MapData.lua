
local _MapData = {}

_MapData[1] = {
	height = 10,
	width = 10,
	name = "liaohua"
}

MapData = {}

function MapData.num()
    return #_MapData
end

function MapData.get(index)
    assert(index >= 1 and index <= #_MapData, string.format("MapData.get() - invalid index %s", tostring(index)))
    return clone(_MapData[index])
end
