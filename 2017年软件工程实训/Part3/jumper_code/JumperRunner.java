/* 
 * A test for a dancing bug
 * @author ugnamsung
 * @datetime 2017-03-26
 */

import info.gridworld.actor.ActorWorld;
import info.gridworld.actor.Bug;
import info.gridworld.actor.Flower;
import info.gridworld.actor.Rock;
import info.gridworld.actor.Actor;

public final class JumperRunner
{
    private JumperRunner(){}

    public static void main(String[] args)
    {

        ActorWorld world = new ActorWorld();
        world.add(new Jumper());
        world.add(new Rock());
        world.show();
    }
}