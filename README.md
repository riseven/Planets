# Planets

*An Irrlicht based game of two gods fighting for the control of a star system.*

This was a flash project. A friend and me decided to do this game in a weekend as an
addition for a presentation we were doing on monday. So after two days of intense
work (and pary, we both partied hard on saturday), this is the result.

It is a two player game with shared screen and keyboard. Each player is a god -ok, its
the Irrlicht engine faery- and moves along a lateral border of the screen. The screen
contains a solar system, with the sun in the centre and the planets circling it. Each
planet adores one god or the other, and one player wins when all the planets follow him.

When a planet has better conditions for life, it will hold more population and therefore
give more mana to the god they follow. Each god needs to improve the conditions of life
of their planets (if there is shortage of water, send a water meteor for example).

Also, gods can attack opposing planets in two ways. They can try to destroy life in the 
planet to reduce the mana of its adversay (sending rock meteors, or so much water that the
planets becomes a waterworld for example). But they can also work to improve the planet
conditions (Sending a fire meteor when the planet is becoming freeze for example) which will
eventually lead to the planet chaning sides.

There are three types of meteor:
 * Fire meteor: Raises planet temperature, too much and the planet will become an unhabited
   desert. Planets slowly loss temperature, and if enought time passes without receiving any
   fire meteor it will eventually become a freeze land unable to sustain life.
 * Water meteor: Raises the water level. A planet can not sustain life without water, but if
   too much water is received the population will windle due to land shortage. If a planet is
   rendered all water, then it will lose all population. I don not remember at this point if
   water slowly disappeared or if the water level decreased when more 'land' was received via
   rock meteors. Any way, if a planet becomes all land will also be unhabitable.
 * Rock meteor: Rock meteors are always negative for population, their effect being the killing
   of people. Of course a planet will slowly recover its population to its natural state based
   on the conditions of the planet.
   
Also, if a player waits to fill one of the bars, it will send a mega meteor for the appropiate 
type, that is always a bad thing for the planet. When a planet receives one of those mega hits
the camera will zoom on it, and show a message of the type of cataclysm that is happening to the
planet:
 * Global warming: When a planet receives a mega fire meteor, it is displayed as Global Warming,
   and the planet becomes a desert.
 * Great flood: When a planet receives a mega water meteor, it is displayed as the Great Flood, 
   and the planet becomes waterworld.
 * Armageddon: When a planet receives a mega rock meteor, it is displayed as the Armageddon, which
   does not modifies the planet conditions, but kills all the population.
   
When a planet loses all population (either via a mega meteor, or because of extremely disruption
of its living conditions) then the planets becomes neutral, and will start following the next god
that does something to improve its living coditions. Hence it is usually easier to win a planet by
exterminating all life on it and then improving its conditions. 

However, the harder task of converting
a planet without extermining it has the advantage that it will have a larger population, and
so it will give more mana from the beginning. The problem is that you are basically improving the 
conditions of a planet which on the short term will give more mana to your adversary.
   