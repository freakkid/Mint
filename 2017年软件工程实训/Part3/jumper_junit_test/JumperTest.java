import org.junit.Before;
import org.junit.After;
import static org.junit.Assert.*;
import org.junit.Test;

import info.gridworld.actor.ActorWorld;
import info.gridworld.actor.Bug;
import info.gridworld.actor.Flower;
import info.gridworld.actor.Rock;
import info.gridworld.actor.Actor;

import info.gridworld.grid.Location;



public class JumperTest {
	public Jumper j1 = new Jumper();
	public Jumper j2 = new Jumper();
	public ActorWorld world = new ActorWorld();
	public Actor a = new Actor();
	public Bug b = new Bug();
	public Rock r = new Rock();
	public Flower f = new Flower();

	@Before
	public void setActorWorld() {
		j1.setDirection(Location.EAST);
		world.add(new Location(2, 2), j1);
	}
	
	@After
	public void clearActorWorld() {
		j1.removeSelfFromGrid();
	}

	@Test
	public void jumpTest() {
		j1.act();
		assertEquals(j1.getLocation(), new Location(2, 4));
		assertEquals(j1.getDirection(), Location.EAST);
		j1.act();
		assertEquals(j1.getLocation(), new Location(2, 6));
		assertEquals(j1.getDirection(), Location.EAST);
	}

	@Test
	public void nextIsFlowerTest() {
		world.add(new Location(2, 4), f);
		j1.act();
		assertEquals(j1.getLocation(), new Location(2, 4));
		assertEquals(j1.getDirection(), Location.EAST);
		assertEquals(f.getGrid(), null);
	}

	@Test
	public void frontIsFlowerTest() {
		world.add(new Location(2, 3), f);
		
		j1.act();
		assertEquals(j1.getLocation(), new Location(2, 4));
		assertEquals(j1.getDirection(), Location.EAST);
		assertEquals(f.getLocation(), new Location(2, 3));
		
		f.removeSelfFromGrid();
	}

	@Test
	public void nextIsRockTest() {
		world.add(new Location(2, 4), r);
		j1.act();
		assertEquals(j1.getLocation(), new Location(2, 2));
		assertEquals(j1.getDirection(), Location.SOUTHEAST);
		assertEquals(r.getLocation(), new Location(2, 4));

		j1.act();
		assertEquals(j1.getLocation(), new Location(4, 4));
		assertEquals(j1.getDirection(), Location.SOUTHEAST);
		assertEquals(r.getLocation(), new Location(2, 4));

		r.removeSelfFromGrid();
	}
	
	@Test
	public void frontIsRockTest() {
		world.add(new Location(2, 3), r);
		j1.act();
		assertEquals(j1.getLocation(), new Location(2, 4));
		assertEquals(j1.getDirection(), Location.EAST);
		r.removeSelfFromGrid();
	}

	@Test
	public void nextIsOutOfGridTest() {
		j1.removeSelfFromGrid();
		j1.setDirection(Location.NORTH);
		world.add(new Location(1, 2), j1);

		j1.act();
		assertEquals(j1.getLocation(), new Location(1, 2));
		assertEquals(j1.getDirection(), Location.NORTHEAST);

		j1.act();
		assertEquals(j1.getLocation(), new Location(1, 2));
		assertEquals(j1.getDirection(), Location.EAST);

		j1.act();
		assertEquals(j1.getLocation(), new Location(1, 4));
		assertEquals(j1.getDirection(), Location.EAST);
		
	}

	@Test
	public void faceEdgeOfGridTest() {
		j1.removeSelfFromGrid();
		j1.setDirection(Location.NORTH);
		world.add(new Location(0, 2), j1);

		j1.act();
		assertEquals(j1.getLocation(), new Location(0, 2));
		assertEquals(j1.getDirection(), Location.NORTHEAST);

		j1.act();
		assertEquals(j1.getLocation(), new Location(0, 2));
		assertEquals(j1.getDirection(), Location.EAST);

		j1.act();
		assertEquals(j1.getLocation(), new Location(0, 4));
		assertEquals(j1.getDirection(), Location.EAST);
	}

	@Test
	public void nextIsAnotherActorTest() {
		world.add(new Location(2, 4), a);

		j1.act();
		assertEquals(j1.getLocation(), new Location(2, 2));
		assertEquals(j1.getDirection(), Location.SOUTHEAST);
		assertEquals(a.getLocation(), new Location(2, 4));

		j1.act();
		assertEquals(j1.getLocation(), new Location(4, 4));
		assertEquals(j1.getDirection(), Location.SOUTHEAST);
		assertEquals(a.getLocation(), new Location(2, 4));

		a.removeSelfFromGrid();
	}

	@Test
	public void faceAnotherJumperTest() {
		j2.setDirection(Location.WEST);
		world.add(new Location(2, 3), j2);

		j1.act();
		j2.act();
		assertEquals(j1.getLocation(), new Location(2, 4));
		assertEquals(j1.getDirection(), Location.EAST);
		assertEquals(j2.getLocation(), new Location(2, 1));
		assertEquals(j2.getDirection(), Location.WEST);

		j2.removeSelfFromGrid();
	}

	@Test
	public void nextIsAnotherJumperTest() {
		j2.setDirection(Location.WEST);
		world.add(new Location(2, 4), j2);

		j1.act();
		j2.act();
		assertEquals(j1.getLocation(), new Location(2, 2));
		assertEquals(j1.getDirection(), Location.SOUTHEAST);
		assertEquals(j2.getLocation(), new Location(2, 4));
		assertEquals(j2.getDirection(), Location.NORTHWEST);

		j1.act();
		j2.act();
		assertEquals(j1.getLocation(), new Location(4, 4));
		assertEquals(j1.getDirection(), Location.SOUTHEAST);
		assertEquals(j2.getLocation(), new Location(0, 2));
		assertEquals(j2.getDirection(), Location.NORTHWEST);

		j2.removeSelfFromGrid();
	}

	@Test
	public void nextIsBugTest() {
		b.setDirection(Location.WEST);
		world.add(new Location(2, 4), b);

		j1.act();
		b.act();
		assertEquals(j1.getLocation(), new Location(2, 2));
		assertEquals(j1.getDirection(), Location.SOUTHEAST);
		assertEquals(b.getLocation(), new Location(2, 3));
		assertEquals(b.getDirection(), Location.WEST);

		j1.act();
		b.act();
		assertEquals(j1.getLocation(), new Location(4, 4));
		assertEquals(j1.getDirection(), Location.SOUTHEAST);
		assertEquals(b.getLocation(), new Location(2, 2));
		assertEquals(b.getDirection(), Location.WEST);

		b.removeSelfFromGrid();		
	}

}