--
-- Created by IntelliJ IDEA.
-- User: aicdg
-- Date: 2017/2/2
-- Time: 10:38
-- To change this template use File | Settings | File Templates.
-- test4.lua
--

require("libmyLuaLib")

local ave,sum = myModule.averageAndSum(1,2,3,4,5)
print(ave,sum)  -- 3 15
myModule.sayHello()   -- hello world!

