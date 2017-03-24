
BeastMove = function (Game, Beast)
--a = Game:LOS (Game.GamerX, Game.GamerY, Beast.CoordX, Beast.CoordY)
a = Game:PathFind (Beast.CoordX, Beast.CoordY,Game.GamerX, Game.GamerY)
--print (a)
end