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
if BeastID<0 then
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
		Game:WeaponMakeOneShot (WeaponID)
		if Game:GetWeaponCurrentAmmoQuantity(WeaponID)== 0 then
			break
		end
	
	end
	return
	end

if BeastID >= 0 then
	ShotInMonster (Game, BeastID)
end
--Game:SetBeastHP (BeastID,-1)

end

ShotInMonster = function (Game, BeastID)
WeaponID = Game:GetIdByGamerSlot(7)
MaxAttack = Game:GetWeaponMaxDamage (WeaponID)
MinAttack = Game:GetWeaponMinDamage (WeaponID)
DeltaAttack = MaxAttack - MinAttack+1
Damage = 0
shots = Game:GetWeaponShotsByStep(WeaponID)
if OneShot == 1 then
	shots = 1
end
	for i = 1,shots do --стреляем очередью и определяем суммарный урон.
	BulletId = Game:GetWeaponNextAmmo(WeaponID)
	BulletMaxDamage = Game:GetWeaponMaxDamage (BulletId)
	BulletMinDamage = Game:GetWeaponMinDamage (BulletId)
	DeltaBulletDamage = BulletMaxDamage-BulletMinDamage+1
	DamageWeapon = MinAttack+Game:MyRandom (DeltaAttack)
	DamageBullet = BulletMinDamage+ Game:MyRandom (DeltaBulletDamage)
	Damage = Damage+ DamageWeapon + DamageBullet
	Game:WeaponMakeOneShot (WeaponID)
	if Game:GetWeaponCurrentAmmoQuantity(WeaponID)== 0 then
		break
	end
	end

BeastHP = Game:GetBeastHP (BeastID);
BeastHP = BeastHP - Damage
if BeastHP <= 0 then
	Game:PrintMessage ("Вы уничтожили эту тварь, нанеся ей "..Damage.." урона." )
	Game:SetBeastHP (BeastID, BeastHP)
end
if BeastHP >0 then
	Game:PrintMessage ("Вы нанесли по твари урон в размере  "..Damage)
	Game:SetBeastHP (BeastID, BeastHP)
end
return
end