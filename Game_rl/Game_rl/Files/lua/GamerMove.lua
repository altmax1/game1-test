TK_RIGHT=0x4F
TK_LEFT=0x50
TK_DOWN=0x51
TK_UP=0x52
TK_KP_1=0x59
TK_KP_2=0x5A
TK_KP_3=0x5B
TK_KP_4=0x5C
TK_KP_5=0x5D
TK_KP_6=0x5E
TK_KP_7=0x5F
TK_KP_8=0x60
TK_KP_9=0x61
PASSABLE= 1
NOT_PASSABLE=0
YES=1
NO=0

GamerMove = function (Game, KeyCode)
NextX = Game.GamerX
NextY = Game.GamerY
if (KeyCode == TK_RIGHT or KeyCode == TK_KP_6) then
	NextX = NextX+1
	Game:SetGamerMoved()
elseif KeyCode == TK_LEFT or KeyCode == TK_KP_4 then
	NextX = NextX-1
	Game:SetGamerMoved()
elseif KeyCode == TK_DOWN or KeyCode == TK_KP_2 then
	NextY = NextY+1
	Game:SetGamerMoved()
elseif KeyCode == TK_UP or KeyCode == TK_KP_8 then
	NextY = NextY-1
	Game:SetGamerMoved()
elseif KeyCode == TK_KP_3 then
	NextY = NextY+1
	NextX = NextX+1
	Game:SetGamerMoved()
elseif KeyCode == TK_KP_1 then
	NextY = NextY+1
	NextX = NextX-1
	Game:SetGamerMoved()
elseif KeyCode == TK_KP_9 then
	NextY = NextY-1
	NextX = NextX+1
	Game:SetGamerMoved()
elseif KeyCode == TK_KP_7 then
	NextY = NextY-1
	NextX = NextX-1
	Game:SetGamerMoved()
	end
Passable = Game:GetCellPassable (NextX, NextY)
if NextX >=0 and NextX < Game:GetLevelWidth () and NextY >= 0 and NextY < Game:GetLevelHeight () then
	LegalCoords = 1
else LegalCoords = 0
end
if Passable == PASSABLE and LegalCoords == 1 then
	Game:SetCellPassable (Game.GamerX, Game.GamerY, PASSABLE)
	Game.GamerX = NextX
	Game.GamerY = NextY
	Game:SetCellPassable (Game.GamerX, Game.GamerY, NOT_PASSABLE)
end
CreatureNum = -1
if Passable == NOT_PASSABLE then
	CreatureNum = Game:GetBeastNumber(NextX, NextY)
	print (CreatureNum)
end
if CreatureNum >= 0 then
	-- вызываем GamerAttack из этого же скрипта:
	Game:AttackBeastByNum (CreatureNum)
	--Game:RemoveCreature (CreatureNum)
	
	
	end

	
end

GamerAttack = function (Game, Beast, NumOfBeast)
print ("GGGGHHYG")
--print (NumOfBeast)
print (Beast.HP)
Beast.HP = Beast.HP-1
if Beast.HP <=0 then
	Game:RemoveCreature (NumOfBeast)
	Beast.IsDead = YES
end
end