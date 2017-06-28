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
Game:AddMessageToLog ("Player Moved!!!"..KeyCode);
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
end
damage = {0,0,0,0,0,0,0,0,0,0}
if CreatureNum >= 0 then
	WeaponID = Game:GetIdByGamerSlot(7)
	NeedsAmmo = Game:GetWeaponNeedsAmmo (WeaponID)
	AmmoQuantity = Game:GetWeaponCurrentAmmoQuantity (WeaponID)
	if NeedsAmmo == 1 and AmmoQuantity == 0 then
		Game:PrintMessage ('Ваше оружие не заряжено. Зарядите его')
		return;
	end
	NeedsEnergy = Game:GetWeaponNeedsEnergy (WeaponID)
	if NeedsEnergy == 1 and AmmoQuantity == 0 then
		Game:PrintMessage ('Ваше оружие не заряжено. Зарядите его')
		return;
	end
	BulletID = Game:GetWeaponNextAmmo (WeaponID)
	BulletQuality = Game:GetItemQuality (BulletID)
	EnergyPerUse = Game:GetWeaponEnergyPerUse (WeaponID)
	if NeedsEnergy == 1 and BulletQuality < EnergyPerUse then
		Game:PrintMessage ("Недостаточный заряд батареи!!!")
		return;
	end
	damage = CalculateDamage (Game)
	print ("Damage  "..damage[1])
	-- вызываем GamerAttack из этого же скрипта:
	Game:AttackBeastByNum (CreatureNum)
	--Game:RemoveCreature (CreatureNum)
	
	
	end

	
end

CalculateDamage = function (Game) --расчёт урона от оружия
	Damage = {0,0,0,0,0,0,0,0,0,0}
	WeaponID = Game:GetIdByGamerSlot(7)
	NeedsAmmo = Game:GetWeaponNeedsAmmo (WeaponID)
	BulletID = Game:GetWeaponNextAmmo (WeaponID)
	NeedsEnergy = Game:GetWeaponNeedsEnergy (WeaponID)
	EnergyPerUse = Game:GetWeaponEnergyPerUse (WeaponID)
	BulletQuality = Game:GetItemQuality (BulletID)
	GamerStr = Game.GamerStr
	GamerDex = Game.GamerDex
	if ( WeaponID <0) then --расчёт физического урона без оружия
		Damage[1] = GamerStr/8+GamerDex/10
		return Damage
	end
	if (NeedsAmmo == 1 ) then -- расчёт урона от выстрела с патронами
		Damage[1] = Game:GetWeaponMaxDamage(WeaponID) - Game:MyRandom (Game:GetWeaponMaxDamage(WeaponID)-Game:GetWeaponMinDamage(WeaponID))
		if Game:GetWeaponDamage2Type(WeaponID)>0 then
			Damage [Game.GetWeaponDamage2Type(WeaponID)] = Game:GetWeaponMaxDamage2(WeaponID) - Game:MyRandom (Game:GetWeaponMaxDamage2(WeaponID)-Game:GetWeaponMinDamage2(WeaponID))
		end
		if Game:GetWeaponDamage3Type(WeaponID)>0 then
			Damage [Game.GetWeaponDamage3Type(WeaponID)] = Game:GetWeaponMaxDamage3(WeaponID) - Game:MyRandom (Game:GetWeaponMaxDamage3(WeaponID)-Game:GetWeaponMinDamage3(WeaponID))
		end
		BulletDamage = Game:GetWeaponMaxDamage(BulletID) - Game:MyRandom (Game:GetWeaponMaxDamage(BulletID)-Game:GetWeaponMinDamage(BulletID))
		Damage[1] = Damage[1]+BuletDamage
		if Game:GetWeaponDamage2Type(BulletID)>0 then
			DamType = Game:GetWeaponDamage2Type(BulletID)
			Dam = Game:GetWeaponMaxDamage2(BulletID) - Game:MyRandom (Game:GetWeaponMaxDamage2(BulletID)-Game:GetWeaponMinDamage2(BulletID))
			Damage[DamType] = Damage[DamType]+dam
		end
		if Game:GetWeaponDamage3Type(BulletID)>0 then
			DamType = Game:GetWeaponDamage3Type(BulletID)
			Dam = Game:GetWeaponMaxDamage3(BulletID) - Game:MyRandom (Game:GetWeaponMaxDamage3(BulletID)-Game:GetWeaponMinDamage3(BulletID))
			Damage[DamType] = Damage[DamType]+dam
		end
		return Damage
	end
	if NeedsEnergy == 1 then --расчёт урона от выстрела энергетическим оружием
		Damage[1] = Game:GetWeaponMaxDamage(WeaponID) - Game:MyRandom (Game:GetWeaponMaxDamage(WeaponID)-Game:GetWeaponMinDamage(WeaponID))
		if Game:GetWeaponDamage2Type(WeaponID)>0 then
			Damage [Game.GetWeaponDamage2Type(WeaponID)] = Game:GetWeaponMaxDamage2(WeaponID) - Game:MyRandom (Game:GetWeaponMaxDamage2(WeaponID)-Game:GetWeaponMinDamage2(WeaponID))
		end
		if Game:GetWeaponDamage3Type(WeaponID)>0 then
			Damage [Game.GetWeaponDamage3Type(WeaponID)] = Game:GetWeaponMaxDamage3(WeaponID) - Game:MyRandom (Game:GetWeaponMaxDamage3(WeaponID)-Game:GetWeaponMinDamage3(WeaponID))
		end
		return Damage
		
	end
	if Game:GetWeaponFacultEnergy(WeaponID) ==1 and BulletQuality>EnergyPerUse then --оружие с факультативной энергоподпиткой
		Damage[1] = Game:GetWeaponMaxDamage(WeaponID) - Game:MyRandom (Game:GetWeaponMaxDamage(WeaponID)-Game:GetWeaponMinDamage(WeaponID))
		if Game:GetWeaponDamage2Type(WeaponID)>0 then
			Damage [Game.GetWeaponDamage2Type(WeaponID)] = Game:GetWeaponMaxDamage2(WeaponID) - Game:MyRandom (Game:GetWeaponMaxDamage2(WeaponID)-Game:GetWeaponMinDamage2(WeaponID))
		end
		if Game:GetWeaponDamage3Type(WeaponID)>0 then
			DamageTemp = Game:GetWeaponMaxDamage3(WeaponID) - Game:MyRandom (Game:GetWeaponMaxDamage3(WeaponID)-Game:GetWeaponMinDamage3(WeaponID))
			Damage [Game.GetWeaponDamage3Type(WeaponID)] = Damage [Game.GetWeaponDamage3Type(WeaponID)]+DamageTemp
		end
		Damage[1] = Damage[1]*GamerStr/8*GamerDex/5
		return Damage
	end
	if Game:GetWeaponFacultEnergy(WeaponID) ==1 and BulletQuality<EnergyPerUse then --оружие с факультативной энергоподпиткой без зарядов
		Damage[1] = Game:GetWeaponMaxDamage(WeaponID) - Game:MyRandom (Game:GetWeaponMaxDamage(WeaponID)-Game:GetWeaponMinDamage(WeaponID))
		if Game:GetWeaponDamage2Type(WeaponID)>0 then
			Damage [Game.GetWeaponDamage2Type(WeaponID)] = Game:GetWeaponMaxDamage2(WeaponID) - Game:MyRandom (Game:GetWeaponMaxDamage2(WeaponID)-Game:GetWeaponMinDamage2(WeaponID))
		end
		Damage[1] = Damage[1]*GamerStr/8*GamerDex/5
		return Damage
	end
	
	--расчёт всего остального оружия
	Damage[1] = Game:GetWeaponMaxDamage(WeaponID) - Game:MyRandom (Game:GetWeaponMaxDamage(WeaponID)-Game:GetWeaponMinDamage(WeaponID))
	if Game:GetWeaponDamage2Type(WeaponID)>0 then
		Damage [Game.GetWeaponDamage2Type(WeaponID)] = Game:GetWeaponMaxDamage2(WeaponID) - Game:MyRandom (Game:GetWeaponMaxDamage2(WeaponID)-Game:GetWeaponMinDamage2(WeaponID))
	end
	if Game:GetWeaponDamage3Type(WeaponID)>0 then
		Damage [Game.GetWeaponDamage3Type(WeaponID)] = Game:GetWeaponMaxDamage3(WeaponID) - Game:MyRandom (Game:GetWeaponMaxDamage3(WeaponID)-Game:GetWeaponMinDamage3(WeaponID))
	end
	Damage[1] = Damage[1]*GamerStr/8*GamerDex/5
	return Damage
	
end

GamerAttack = function (Game, Beast, NumOfBeast)
--print ("GGGGHHYG")
--print (NumOfBeast)
--print (Beast.HP)
Beast.HP = Beast.HP-1
if Beast.HP <=0 then
	Game:RemoveCreature (NumOfBeast)
	Beast.IsDead = YES
end
end