/*************************************************************\
*  Larkin List       *
\*************************************************************/
#ifndef LRListH
#define LRListH
#define LRList Int
/*
//объявлять с пом int b[] = {1,2,3,4,}
//Это список с возможностью []
clear, delete, exchange пом местами, insert, savetofile, сортировка, addSort */
class LRList
{
protected:
   struct Data
   {
      int Store;
      Data *next;
      Data *prev;
   }
   *Begin, *End, *Linker;

   int FCount;
   int Mid;
   int getCount()  {   return (FCount);    }
   void setCount(int newCount)    { FCount = newCount; Mid = FCount/2;   }
   void setStore(int newCount) { FCount = newCount; }
   void DeleteLinks (Data *Item);
   bool NumbFromZero;
   int getStore(int index);
   void concatenate(Data *parent, Data *Item);  


public:
   LRList(int mem = 0); //Конструктор
   void Add(int a);
   __property int Count = { read=FCount, write=setCount };
   void Clear();
   //LRList& operator+ (LRList & A, LRList & B);   //нельзя
   LRList operator+ (LRList & A);   //Бинарная
   LRList operator+ ();               //Унарная
   Data & Find ( int index );         
   int & operator[](int position)   {   return Find(position).Store;    }


   //или тип LRList& ?
void Erase(int position)
{
   if ( FCount == 0 )
      return;
   if ( FCount == 1 )
   {
      Clear();
      return;
   }   
   Data &DeletedItem = Find(position);
   if ( position <= 0 )
      Begin=Begin->next;
   if ( position >= FCount-1)
      End=End->prev;
   concatenate(DeletedItem.prev,DeletedItem.next);   
   delete &DeletedItem;
   Count--;
   
}       
   ~LRList()
   {
      ShowMessage("destructooor "+IntToStr(FCount));
      Clear();
   }
};  //КЛАСС

LRList::LRList(int mem)
   {
     // nizn = new int[3];
      ShowMessage("constr run with "+IntToStr(mem));
      //Qdialogs::ShowMessage("Деструктор запущен");
      //Store = mem;
      FCount = 0;
      Mid = 0;
      NumbFromZero = true;
      Begin = NULL;
      End = NULL;
   }

void LRList::Add(int a)
{
   Count++;   
   Data *pItem = new Data;
   pItem->Store=a;
   pItem->next=NULL;
   pItem->prev=End;
   if (Begin == NULL)
      Begin = pItem;
   else
      End->next=pItem;
   End=pItem;
}

   LRList::Data & LRList::Find ( int position )
   {
      if ( position > Mid )
      {  //C конца
         Linker = End;
         for (int i=FCount-1;i>position;i--)
            Linker=Linker->prev;
      }
      else
      {  //C начала
         Linker = Begin;
         for (int i=0;i<position;i++)
            Linker=Linker->next;
      }
      return *Linker;
   }
   int LRList::getStore(int position)
   {
      Data *Linker = Begin;
      for (int i=0;i<position;i++)
         Linker=Linker->next;
      return (Linker->Store);
   }

void LRList::DeleteLinks (Data *Item)
{               //Функция удаляет список
   if (Item == NULL) return;
   if (Item->next != NULL)
   {
      DeleteLinks (Item->next);
   }
   delete Item;
   Item=NULL;
}

void LRList::Clear()
{
   DeleteLinks(Begin);
   FCount=0;
   Mid=0;
   Begin = NULL;
   End = NULL;
}


LRList LRList::operator+ (LRList & A)
{
   LRList temp;
   //this->Store=5;
   return temp;
}

LRList& operator + (LRList & A, LRList & B)
{
   LRList *hp;
   return *hp;
}

void LRList::concatenate(Data *parent, Data *Item)  //REMARKABLE!
{              //Функция соединяет два элемента
     if (parent != NULL)
          parent->next=Item;
     if (Item!=NULL)
          Item->prev=parent;
}

class LRList2 : public LRList
{
   public:
   void DeleteLast()
   {
      if (End == NULL)
         return;
      if (FCount == 1)
      {
         Clear();
         return;
      }
      End=End->prev;
      delete End->next;
      Count--;
   }
};


class PropertyExample {

private:
		int Fx,Fy;
		float Fcells[100][100];
	protected:
		int  readX()          { return(Fx); }
		void writeX(int newFx) { Fx = newFx;  }
		double computeZ() { 
				// Do some computation and return a floating point value...
				return(0.0);
		}

		float cellValue(int row, int col) { return(Fcells[row][col]); }
	public:

__property int    X = { read=readX, write=writeX };
		__property int    Y = { read=Fy };
		__property double Z = { read=computeZ };
		__property float Cells[int row][int col] = { read=cellValue };
};

#endif
 