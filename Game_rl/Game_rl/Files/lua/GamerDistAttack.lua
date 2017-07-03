GamerDistAttack = function (Game)
Coords = Game:SelectTarget()
OneShot = 0
if Coords > 1000000000 then
	Coords = Coords-1000000000
	OneShot = 1
end

CoordX = math.floor(Coords/1000)
CoordY = math.fmod (Coords,1000)
WeaponID = Game:GetIdByGamerSlot(7)
Los = Game:LOS (Game.GamerX, Game.GamerY, CoordX, CoordY)
if Los == 0 then
	Game:PrintMessage ('Вы не можете выстрелить туда - цель скрыта')
	return
end
if WeaponID == -1 then --проверяем наличие оружия
	Game:PrintMessage ('У вас нет соответствующего оружия')
	return
end
BeastID = Game:GetBeastNumber (CoordX, CoordY)
print ("BeastID  "..BeastID)
print (BeastID)
Distance = ((Game.GamerX-CoordX)^2+(Game.GamerY-CoordY)^2)^0.5
WeaponRange = Game:GetWeaponRange (WeaponID)
if Distance>WeaponRange then -- проверяем дистанцию до цели
	Game:PrintMessage ('Ваше оружие недостаточно дальнобойно чтобы нанести урон по указанному месту')
	return
end
NeedsAmmo = Game:GetWeaponNeedsAmmo (WeaponID)
AmmoQuantity = Game:GetWeaponCurrentAmmoQuantity (WeaponID)

if NeedsAmmo == 1 and AmmoQuantity == 0 then -- проверяем патроны/заряды
	Game:PrintMessage ('Ваше оружие не заряжено. Зарядите его')
	return;
end
BulletId = Game:GetWeaponNextAmmo (WeaponID)
if Game:GetWeaponBlastRadius (BulletId) >0 or Game:GetWeaponBlastRadius (WeaponID)>0 then -- атака по площадям еcли BlastRadius >0
	
	shots = Game:GetWeaponShotsByStep(WeaponID)
	if OneShot == 1 then
		shots = 1
	end
	for i = 1,shots do
		MassAttack (Game, CoordX, CoordY)
		Game:WeaponMakeOneShot (WeaponID)
		if Game:GetWeaponCurrentAmmoQuantity(WeaponID)== 0 then
			break
		end
	
	end
	return
end

if BeastID<0 then --если клетка пустая
	Game:PrintMessageNow ("Там никого нет. Вы действительно хотите туда выстрелить? (Y для выстрела)")
	Code = Game:GetKeyCode()
	if Code ~= 28 then
	return
	end
	shots = Game:GetWeaponShotsByStep(WeaponID)
	if OneShot == 1 then
		shots = 1
	end
	for i = 1,shots do
		print ("Shoting!!!")
		BulletId = Game:GetWeaponNextAmmo (WeaponID)
		if Game:GetWeaponAfterEffectType (WeaponID) > 0 or Game:GetWeaponAfterEffectType (BulletId)>0 then
		AddAfterEffect (Game,CoordX, CoordY, WeaponID, BulletId)
		end
		Game:WeaponMakeOneShot (WeaponID)
		if Game:GetWeaponCurrentAmmoQuantity(WeaponID)== 0 then
			break
		end
	
	end
	return
	end

if BeastID >= 0 then
	ShotInMonster (Game, BeastID, CoordX, CoordY)
end
--Game:SetBeastHP (BeastID,-1)

end

ShotInMonster = function (Game, BeastID, CoordX, CoordY)
WeaponID = Game:GetIdByGamerSlot(7)
MaxAttack = Game:GetWeaponMaxDamage (WeaponID)
MinAttack = Game:GetWeaponMinDamage (WeaponID)
DeltaAttack = MaxAttack - MinAttack+1
Damage = 0
shots = Game:GetWeaponShotsByStep(WeaponID)
BeastDefense = Game:GetBeastDefense (BeastID)
if OneShot == 1 then
	shots = 1
end
	for i = 1,shots do --стреляем очередью и определяем суммарный урон.
	BulletId = Game:GetWeaponNextAmmo(WeaponID)
	AddAfterEffect (Game, CoordX, CoordY, WeaponID, BulletId)
	BulletMaxDamage = Game:GetWeaponMaxDamage (BulletId)
	BulletMinDamage = Game:GetWeaponMinDamage (BulletId)
	DeltaBulletDamage = BulletMaxDamage-BulletMinDamage+1
	DamageWeapon = MinAttack+Game:MyRandom (DeltaAttack)
	DamageBullet = BulletMinDamage+ Game:MyRandom (DeltaBulletDamage)
	TempDamage = DamageWeapon + DamageBullet-BeastDefense
	if TempDamage < 0 then
		TempDamage = 0
	end
	Damage = Damage+ TempDamage
	Game:WeaponMakeOneShot (WeaponID)
	if Game:GetWeaponCurrentAmmoQuantity(WeaponID)== 0 then
		break
	end
	end

BeastHP = Game:GetBeastHP (BeastID);
BeastHP = BeastHP - Damage
BeastName = Game:GetBeastRName (BeastID)
if BeastHP <= 0 then
	Game:PrintMessage ("Вы уничтожили <<"..BeastName..">>, нанеся ей "..Damage.." урона." )
	Game:SetBeastHP (BeastID, BeastHP)
end
if BeastHP >0 then
	Game:PrintMessage ("Вы нанесли по <<"..BeastName..">> урон в размере  "..Damage)
	Game:SetBeastHP (BeastID, BeastHP)
end
return
end

MassAttack = function (Game, CoordX, CoordY)

Width = Game:GetLevelWidth()
Height = Game:GetLevelHeight()

WeaponID = Game:GetIdByGamerSlot(7)
BulletId = Game:GetWeaponNextAmmo(WeaponID)
BlastRadius = Game:GetWeaponBlastRadius (BulletId)
BulletMaxDamage = Game:GetWeaponMaxDamage (BulletId)
BulletMinDamage = Game:GetWeaponMinDamage (BulletId)
DeltaBulletDamage = BulletMaxDamage-BulletMinDamage+1
DamageBullet = BulletMinDamage+ Game:MyRandom (DeltaBulletDamage)
Damage = DamageBullet
for y = -BlastRadius, BlastRadius do
	for x = -BlastRadius, BlastRadius do
		NewCoordX = CoordX + x
		NewCoordY = CoordY + y
		Los = Game:LOS( NewCoordX, NewCoordY, CoordX, CoordY)
		Tile = Game:GetTileBaseType (NewCoordX, NewCoordY)
		if NewCoordX >=1 and NewCoordX <= Width and NewCoordY >= 1 and NewCoordY < Height and Los == 1 and Tile == '.' then
		AddAfterEffect (Game, NewCoordX, NewCoordY, WeaponID, BulletId)
		BeastID = Game:GetBeastNumber (NewCoordX, NewCoordY)
			if BeastID>=0 then
				BeastHP = Game:GetBeastHP (BeastID);
				BeastDefense = Game:GetBeastDefense (BeastID)
				TempDamage = DamageBullet-BeastDefense
				if TempDamage < 0 then
				TempDamage = 0
				end
				BeastHP = BeastHP - TempDamage
				BeastName = Game:GetBeastRName (BeastID)
				if BeastHP <= 0 then
					Game:PrintMessage ("Вы уничтожили <<"..BeastName..">>, нанеся ей "..TempDamage.." урона." )
					Game:SetBeastHP (BeastID, BeastHP)
				end
			if BeastHP >0 then
				Game:PrintMessage ("Вы нанесли по <<"..BeastName..">> урон в размере  "..TempDamage)
				Game:SetBeastHP (BeastID, BeastHP)
			end
			
			end
		end
	
	end
end
end

AddAfterEffect = function (Game, CoordX, CoordY, WeaponID, BulletId)
if Game:GetWeaponAfterEffectType (WeaponID) >0 then
Type = Game:GetWeaponAfterEffectType (WeaponID)
Time = Game:GetWeaponAfterEffectTime (WeaponID)
Power = Game:GetWeaponAfterEffectPower (WeaponID)
Game:AddEffectOnCell (CoordX, CoordY, Type, Power, Time)
end

if Game:GetWeaponAfterEffectType (BulletId) >0 then
Type = Game:GetWeaponAfterEffectType (BulletId)
Time = Game:GetWeaponAfterEffectTime (BulletId)
Power = Game:GetWeaponAfterEffectPower (BulletId)
Game:AddEffectOnCell (CoordX, CoordY, Type, Power, Time)
end



end