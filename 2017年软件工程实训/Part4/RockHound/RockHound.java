import info.gridworld.actor.Actor;
import info.gridworld.actor.Rock;
import info.gridworld.actor.Critter;
import info.gridworld.grid.Location;

import java.awt.Color;
import java.util.ArrayList;

public class RockHound extends Critter
{
 	// a critter can eat rock
    public void processActors(ArrayList<Actor> actors)
    {
        for (Actor a : actors)
        {	
        	// check if a rock
        	// eat rock
            if (a instanceof Rock) {
                a.removeSelfFromGrid();
            }
        }
    }

}
