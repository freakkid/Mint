/* 
 * A test for a circleBug running by spiral pattern
 * 
 * @datetime 2017-03-25
 * @author Cay Horstmann
 */

import info.gridworld.actor.ActorWorld;


/**
 * This class runs a world that contains a bug, added at random
 * locations. Click on empty locations to add additional actors. Click on
 * populated locations to invoke methods on their occupants. <br />
 * To build your own worlds, define your own actors and a runner class. See the
 * BoxBugRunner (in the boxBug folder) for an example. <br />
 * This class is not tested on the AP CS A and AB exams.
 */

public final class SpiralBugRunner
{
    private SpiralBugRunner(){}

    public static void main(String[] args)
    {
        final int num = 4;
        ActorWorld world = new ActorWorld();
        world.add(new SpiralBug(num));
        world.show();
    }
}