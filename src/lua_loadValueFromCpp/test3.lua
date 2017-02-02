--
-- Created by IntelliJ IDEA.
-- User: aicdg
-- Date: 2017/2/2
-- Time: 9:00
-- To change this template use File | Settings | File Templates.
-- test3.lua
--

-- 1. 从C++中读取值
print("C++中的值 = " .. valueFromCpp)

-- 2. 从C++中读取函数
avg, sum = averageAndSum(10, 20, 30, 40, 50)
print("The average is ", avg)
print("The sum is ", sum)
