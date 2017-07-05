MakeLevel = function (Game, Level)
	print ("LevelNum".. Level:GetLevelNum())-- == 1 then -- делаем самый первый уровень
	Level:MakeDungeon (1,128,40,40)
	--end
end