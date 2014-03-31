local initconnection = require("debugger")
initconnection('127.0.0.1', 10000, 'luaidekey')


-- for CCLuaEngine
function __G__TRACKBACK__(errorMessage)
    print("----------------------------------------")
    print("LUA ERROR: "..tostring(errorMessage).."\n")
    print(debug.traceback("", 2))
    print("----------------------------------------")
end

require("app.MyApp").new():run()