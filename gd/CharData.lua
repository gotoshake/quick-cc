
local _CharData = {}

_CharData[1] = {
	wl = 10,
	ts = 10,
	zl = 10,
	zz = 10,
	ml = 10,
}

_CharData[2] = {
	wl = 11,
	ts = 11,
	zl = 11,
	zz = 11,
	ml = 11,
}

CharData = {}
function CharData.numChars()
    return #_CharData
end

function CharData.get(index)
    assert(index >= 1 and index <= #_CharData, string.format("CharData.get() - invalid index %s", tostring(index)))
    return clone(_CharData[index])
end
