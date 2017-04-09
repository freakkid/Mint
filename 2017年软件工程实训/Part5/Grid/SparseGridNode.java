

public class SparseGridNode
{
	private Object occupant;
	private int col;
	private SparseGridNode next;
	
	public SparseGridNode(Object a, int c)
	{
		occupant = a;
		col = c;
		next = null;
	}

	public void setCol(int c)
	{
		col = c;
	}

	public void setOccupant(Object a)
	{
		if (a != null)
			occupant = a;
	}

	public void setNext(SparseGridNode n)
	{
		next = n;
	}

	public int getCol()
	{
		return col;
	}

	public Object getOccupant()
	{
		return occupant;
	}

	public SparseGridNode getNext()
	{
		return next;
	}

}

