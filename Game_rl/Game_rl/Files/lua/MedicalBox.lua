local MedicalBox = {}

TK_RIGHT =  0x4F
TK_LEFT  =  0x50
TK_DOWN  =  0x51
TK_UP    =  0x52
TK_ESCAPE = 0x29
TK_ENTER =  0x28
TK_TAB   =  0x2B


MedicalBoxStart = function (Game)
	CurrentPos = 1
	MaxPos = 10
	ItemsYouHave = {}
	ItemsToUse = {}
	for i = 1,10,1 do
		ItemsYouHave[i] = 0
		ItemsToUse[i] = 0
	end
	ItemsYouHave[3] = 25
	ItemsYouHave[7] = 167
	FindQuantity (Game)
	while (1) do
	Game:Terminal_clear()
	Game:Terminal_print(10,1,"Медицинский автоматизированный бокс")
	PrintList(Game)
	Game:Terminal_refresh()
	a = Game:Terminal_read()
	ExecuteCom (Game, a)
	if a== TK_ESCAPE then
		break
	end
	end

end

PrintList = function (Game)


Game:Terminal_print (37,4,"ИМЕЕТСЯ")
Game:Terminal_print (49,4,"ИСПОЛЬЗОВАТЬ")
Game:Terminal_print (5,6,"Серый споран")
Game:Terminal_print (5,7,"Красный споран")
Game:Terminal_print (5,8,"Желтый споран")
Game:Terminal_print (5,9,"Зеленый споран")
Game:Terminal_print (5,10,"Синий споран")
Game:Terminal_print (5,11,"Белый споран")
Game:Terminal_print (5,12,"Черный споран")
Game:Terminal_print (5,13,"Зародыш спорана (горох)")
Game:Terminal_print (5,14,"Споронить")
Game:Terminal_print (5,15,"Капсула с ядом")
Game:Terminal_print (2,CurrentPos+5, ">>")
Game:Terminal_print (41, CurrentPos+5,"<")
Game:Terminal_print (37, CurrentPos+5,">")
Game:Terminal_print (56, CurrentPos+5,"<")
Game:Terminal_print (52, CurrentPos+5,">")

Game:Terminal_color (0xFF7F7F7F)
Game:Terminal_print (0,20,"Используйте стрелки вверх/вниз для навигации, вправо/влево - изменить значение")
Game:Terminal_print (0,21,"на 1. ENTER - ввести значение вручную, TAB - использовать максимальное кол-во")
Game:Terminal_print (0,22,"Для запуска процедуры экстракции и получения инъектора нажмите R")
Game:Terminal_color (0xffffffff)

for i = 1,10,1 do
	x1=0
	x2=0
	if ItemsYouHave[i] > 9 and ItemsYouHave[i] <100 then
	x1 = 1
	end
	if ItemsYouHave[i] > 99 and ItemsYouHave[i] <1000 then
	x1 = 2
	end
	if ItemsToUse[i]>9 and ItemsToUse[i]<100 then
	x2 = 1
	end
	if ItemsToUse[i]>99 and ItemsToUse[i]<1000 then
	x2 = 2
	end
	Game:Terminal_print (40-x1, 5+i, ItemsYouHave[i])
	Game:Terminal_print (55-x2, 5+i, ItemsToUse[i])
end


end

ExecuteCom = function(Game, a)

if a == TK_DOWN and CurrentPos<MaxPos then
	CurrentPos = CurrentPos+1
end

if a==TK_UP and CurrentPos >1 then
	CurrentPos = CurrentPos-1
end

if a == TK_ENTER then
	EnterValue(Game)
end

if a == TK_TAB then
	MakeMaxValue()
end

if a == TK_RIGHT then
	ValueUp()
end

if a == TK_LEFT then
	ValueDown()
end

end

EnterValue = function (Game)
	Game:Terminal_print (0,35, "Введите количество:" )
	Value = Game:GetInputNumber()
	if Value <= ItemsYouHave[CurrentPos] then
		ItemsToUse[CurrentPos] = Value
	end
	if Value > ItemsYouHave[CurrentPos] then
		ItemsToUse[CurrentPos] = ItemsYouHave[CurrentPos]
	end
end

MakeMaxValue = function()
	ItemsToUse[CurrentPos] = ItemsYouHave[CurrentPos]
end

ValueDown = function()
	if ItemsToUse[CurrentPos]>0 then
		ItemsToUse[CurrentPos] = ItemsToUse[CurrentPos]-1
	end
end

ValueUp = function()
	if ItemsToUse[CurrentPos] < ItemsYouHave[CurrentPos] then
		ItemsToUse[CurrentPos] = ItemsToUse[CurrentPos]+1
	end
end

FindQuantity  = function (Game)

for i =1,10,1 do
ItemsYouHave[i] = Game:GetQuantityByID(2900000+i)
end

end

return MedicalBox