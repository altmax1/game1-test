local MedicalBox = {}

MedicalBoxStart = function (Game)
	a=12343345
	Game:Terminal_clear()
	Game:Terminal_print(10,3,"Медицинский автоматизированный бокс")
	Game:Terminal_refresh()
	a = Game:Terminal_read()

end

return MedicalBox