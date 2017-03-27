/* 
 * A test for a dancing bug
 * @datetime 2017-03-25
 */

import info.gridworld.actor.ActorWorld;
;

/**
 * This class runs a world that contains a bug added at random
 * locations. Click on empty locations to add additional actors. Click on
 * populated locations to invoke methods on their occupants. <br />
 * To build your own worlds, define your own actors and a runner class. See the
 * Dancing bug for an example. <br />
 * This class is not tested on the AP CS A and AB exams.
 */
public final class DancingBugRunner
{
    private DancingBugRunner(){}

    public static void main(String[] args)
    {
        final int array[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2};
        
        ActorWorld world = new ActorWorld();
        world.add(new DancingBug(array));
        world.show();
    }
}