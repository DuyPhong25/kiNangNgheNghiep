#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<string.h>
#include<time.h>
// Dinh nghia cau truc toa do
typedef struct
{
	int x, y;
}ToaDo;

ToaDo Head, Tail, Body;
ToaDo TD[401];
int demTD = 0, demV = 90;
int DoDai = 2, CheckAnV = 0, CheckV = 0, ktDoAnV = 0;
int DiemCT = 0, DiemOLD = 0, DiemV = 0;
ToaDo DoAn, DoAnV;
int doKho = 100;

int wherex() // ham tra ve vi tri cua cot hien hanh
{
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	return coninfo.dwCursorPosition.X;
}

int wherey() // ham tra ve vi tri cua hang hien hanh
{
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	return coninfo.dwCursorPosition.Y;
}

void gotoxy(int x, int y) // ham di chuyen con tro den cot thu x va hang thu y
{
	static HANDLE  h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x,y };
	SetConsoleCursorPosition(h, c);
}

void SetTeColor(WORD color) //ham tao mau chu
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0; wAttributes |= color;
	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void ThongTin() //ham tao thong tin
{
	SetTeColor(13);
	gotoxy(15, 2);
	SetTeColor(14);
	printf("\t\t\tSS004.K22.7\n");
	printf("\t\t\tVo Duy Phong - 19522016\n");
	printf("\t\t\tNguyen Thu Thu Hang - 19521469\n");
	printf("\t\t\tNguyen Thi Cam Thuy - 19520294\n");
	printf("\t\t\tNguon: Vforum.vn\n");
	printf("\n\n");
}

void reset(); // ham reset lai cac thong so ban dau
void intro(); // ham xuat thong tin
void menu();  //ham tao ban dieu khien, chon do kho va huong dan choi
void menuchon(int chon, int choncu); //ham xu ly trong bang dieu kien
void xuatDiem();  //ham xuat diem khi dang choi
int DieuKhien(int n, int x, int y); //ham dieu khien ran khi bat dau choi
void DiNgangT(int x, int y); //ham dieu khien ran di chuyen ngang ben phai
void DiLen(int x, int y); //ham dieu khien ran di chuyen len
void DiXuong(int x, int y); //ham dieu khien ran di chuyen xuong
void DiNgangL(int x, int y); ////ham dieu khien ran di chuyen ngang ben trai
void xoaTail(ToaDo cuoi); //ham xoa toa do cuoi
ToaDo ViTriDau(); 
int Check(); //ham kiem tra khi nao ran died
void inDoAn(ToaDo DoAn); //ham in do an
void XoaDoAn(ToaDo DoAn); //ham xoa do an khi ran da an
void TaoDoAn(); // ham tao do an (random)
void TaoDoAnV(); //ham tao do an lon (sau khi ran an 5 do an nho)
void Khung(); //tao giao dien game
int main()
{
	menu();
	system("cls");
	Khung();
	srand(time(NULL));
	gotoxy(2, 10);
	Head = ViTriDau();
	Body = Head;
	Body.x = 1;
	TD[0] = Body;
	TD[1] = Head;
	TaoDoAn();
	DiNgangT(Head.x, Head.y);

}
int DieuKhien(int n, int x, int y) //ham dieu khien ran khi bat dau choi
{
	SetTeColor(2);
	if (DiemCT > DiemOLD)
	{
		TaoDoAn();
		DiemOLD = DiemCT;
		if (DiemCT % 5 == 0)
			ktDoAnV = 0;
		ktDoAnV = 0;
	}
	if (DiemCT != 0 && DiemCT % 5 == 0 && CheckV == 0 && ktDoAnV == 0)
	{
		TaoDoAnV();
		CheckV = 1;
	}
	if (CheckV == 1)
	{
		demV--;
	}
	if (CheckV == 0 || demV == 0)
	{
		demV = 90;
		XoaDoAn(DoAnV);
		CheckV = 0;
		ktDoAnV = 1;
	}
	xuatDiem();
	if (Check() == 1)
		if (_kbhit())
		{
			int a = _getch();
			if (n == 4 || n == 2)
			{
				if (a == 115)
					DiXuong(x, y);
				if (a == 119)
					DiLen(x, y);
			}
			if (n == 1 || n == 3)
			{
				if (a == 100)
					DiNgangT(x, y);
				if (a == 97)
					DiNgangL(x, y);
			}
			if (a == 112)
			{
				gotoxy(1, 21);
				printf("                 ");
				while (1)
				{
					if (_kbhit())
					{
						int p = _getch();
						if (p == 112)
							break;
						if (p == 27)
						{
							reset();
							main();
						}
					}
					gotoxy(10, 21);
					Sleep(100);
					printf("DANG TAM DUNG BAM p DE TIEP TUC -- BAM ESC DE QUAY LAI MENU");
					gotoxy(10, 21);
					Sleep(100);
					printf("                                                           ");
				}

			}
			// s = 115    		== 1
			// a = 97		== 2
			// w = 119		== 3
			// d = 100		== 4
		}
	if (Check() == 0)
	{
		system("cls");
		SetTeColor(12);
		printf("\t\tYOU DIED\n");
		printf("\tDiem cua ban la : %d \n\n", DiemCT + DiemV);
		char tmp;
		SetTeColor(15);
		printf("\tBAM ENTER DE CHOI LAI\n\tBAM ESC DE THOAT LUON");
		while (1)
		{
			tmp = _getch();
			if (tmp == 13)
			{
				reset();
				main();
			}
			if (tmp == 27)
			{
				printf("\n\t\t\tTam biet va hen gap lai!\n\n\n");
				printf("Thoat trong 3s");
				Sleep(3000);
				exit(1);
			}
		}
		exit(1);
	}
	return 0;
}
void DiNgangT(int x, int y) //ham dieu khien ran di chuyen ngang ben phai
{
	while (1)
	{
		Sleep(doKho);
		gotoxy(++x, y);
		printf("%c", 1);
		if (x == DoAn.x && y == DoAn.y)
		{
			DiemCT++;
			DoDai++;
			printf("%c", 7);
			goto daira;
		}
		if (x == DoAnV.x && y == DoAnV.y)
		{
			CheckAnV = 1;
			CheckV = 0;
			DiemV += demV;
			ktDoAnV = 1;
		}
		xoaTail(TD[0]);
		for (int i = 0; i < DoDai - 1; i++)
			TD[i] = TD[i + 1];
	daira:;
		gotoxy(x, y);
		Head = ViTriDau();
		TD[DoDai - 1] = Head;
		DieuKhien(4, x, y);
	}
}
void DiNgangL(int x, int y) //ham dieu khien ran di chuyen ngang ben trai
{
	while (1)
	{
		Sleep(doKho);
		gotoxy(--x, y);
		printf("%c", 1);
		if (x == DoAn.x && y == DoAn.y)
		{
			DiemCT++;
			DoDai++;
			printf("%c", 7);
			goto daira;
		}
		if (x == DoAnV.x && y == DoAnV.y)
		{
			CheckAnV = 1;
			CheckV = 0;
			DiemV += demV;
			ktDoAnV = 1;
		}
		xoaTail(TD[0]);
		for (int i = 0; i < DoDai - 1; i++)
			TD[i] = TD[i + 1];
	daira:;
		gotoxy(x, y);
		Head = ViTriDau();
		TD[DoDai - 1] = Head;
		DieuKhien(4, x, y);
	}
}
void DiLen(int x, int y) //ham dieu khien ran di chuyen len
{
	while (1)
	{
		Sleep(doKho);
		gotoxy(x, --y);
		printf("%c", 1);
		if (x == DoAn.x && y == DoAn.y)
		{
			DiemCT++;
			DoDai++;
			printf("%c", 7);
			goto daira;
		}
		if (x == DoAnV.x && y == DoAnV.y)
		{
			CheckAnV = 1;
			CheckV = 0;
			DiemV += demV;
			ktDoAnV = 1;
		}
		xoaTail(TD[0]);
		for (int i = 0; i < DoDai - 1; i++)
			TD[i] = TD[i + 1];
	daira:;
		gotoxy(x, y);
		Head = ViTriDau();
		TD[DoDai - 1] = Head;
		DieuKhien(3, x, y);
	}
}
void DiXuong(int x, int y) //ham dieu khien ran di xuong
{
	while (1)
	{
		Sleep(doKho);
		gotoxy(x, ++y);
		printf("%c", 1);
		if (x == DoAn.x && y == DoAn.y)
		{
			DiemCT++;
			DoDai++;
			printf("%c", 7);
			goto daira;
		}
		if (x == DoAnV.x && y == DoAnV.y)
		{
			CheckAnV = 1;
			CheckV = 0;
			DiemV += demV;
			ktDoAnV = 1;
		}
		xoaTail(TD[0]);
		for (int i = 0; i < DoDai - 1; i++)
			TD[i] = TD[i + 1];
	daira:;
		gotoxy(x, y);
		Head = ViTriDau();
		TD[DoDai - 1] = Head;
		DieuKhien(3, x, y);
	}
}
ToaDo ViTriDau() // ham tao vi tri ban dau cho ran
{
	ToaDo Dau;
	Dau.x = wherex();
	Dau.y = wherey();
	return Dau;
} 
void TaoDoAn() // ham random tao do an
{
	int check = 0;
	do
	{
		DoAn.x = 2 + rand() % 77;
		DoAn.y = 2 + rand() % 18;
		for (int i = 0; i < DoDai; i++)
		{
			if (TD[i].x == DoAn.x && TD[i].y == DoAn.y)
			{
				check = 1;
				break;
			}
		}
		if (check == 0)
		{
			SetTeColor(14);
			inDoAn(DoAn);
		}
	} while (check == 1);
}
void TaoDoAnV() //ham tao do an
{
	int check = 0;
	do
	{
		DoAnV.x = 2 + rand() % 77;
		DoAnV.y = 2 + rand() % 18;
		if (DoAnV.x == DoAn.x && DoAnV.y == DoAn.y)
		{
			check = 1;
			continue;
		}
		for (int i = 0; i < DoDai; i++)
		{
			if (TD[i].x == DoAnV.x && TD[i].y == DoAnV.y)
			{
				check = 1;
				break;
			}
		}
		if (check == 0)
		{
			SetTeColor(13);
			inDoAn(DoAnV);
		}
	} while (check == 1);
}
void inDoAn(ToaDo DoAn) //ham in do an
{
	gotoxy(DoAn.x, DoAn.y);
	printf("*");
}
void XoaDoAn(ToaDo DoAn) //ham xoa do an
{
	gotoxy(DoAn.x, DoAn.y);
	printf(" ");
}
void xuatDiem() //ham xuat diem khi dang choi
{
	gotoxy(1, 21);
	printf("BAM p DE TAM DUNG");
	gotoxy(1, 22);
	printf("DIEM CUA BAN LA: %d", DiemCT + DiemV);
}
void xoaTail(ToaDo cuoi) //ham xoa toa do cuoi khi ran di chuyen
{
	gotoxy(cuoi.x, cuoi.y);
	printf(" ");
}
int Check() // ham kiem tra ran chet (khi ran cham vao tuong va khi ran cham vao ban than)
{
	if (Head.x == 0 || Head.x == 79 || Head.y == 0 || Head.y == 20)
		return 0;
	for (int i = 0; i < DoDai - 1; i++)
		if (TD[i].x == Head.x && TD[i].y == Head.y)
			return 0;
	return 1;
}
void intro() //ham xuat thong tin
{
	system("cls");
	SetTeColor(12);
	ThongTin();
	SetTeColor(15);
	printf("Bam enter de qua lai luc nay");
	char enter;
	while (1)
	{
		enter = _getch();
		if (enter == 13)
			break;
	}
	menu();
}
void Khung() //ham tao giao dien khi bat dau choi game
{
	for (int i = 0; i < 80; i++)
	{
		if (i == 79)
			printf("%c", 3);
		if (i < 79)
			printf("%c", 31);
	}
	printf("%c                                                                              %c", 16, 17);
	printf("%c                                                                              %c", 16, 17);
	printf("%c                                                                              %c", 16, 17);
	printf("%c                                                                              %c", 16, 17);
	printf("%c                                                                              %c", 16, 17);
	printf("%c                                                                              %c", 16, 17);
	printf("%c                                                                              %c", 16, 17);
	printf("%c                                                                              %c", 16, 17);
	printf("%c                                                                              %c", 16, 17);
	printf("%c                                                                              %c", 16, 17);
	printf("%c                                                                              %c", 16, 17);
	printf("%c                                                                              %c", 16, 17);
	printf("%c                                                                              %c", 16, 17);
	printf("%c                                                                              %c", 16, 17);
	printf("%c                                                                              %c", 16, 17);
	printf("%c                                                                              %c", 16, 17);
	printf("%c                                                                              %c", 16, 17);
	printf("%c                                                                              %c", 16, 17);
	printf("%c                                                                              %c", 16, 17);
	for (int i = 0; i < 80; i++)
	{
		if (i == 79)
			printf("%c", 3);
		if (i < 79)
			printf("%c", 30);
	}
}
void menu() //ham tao menu dieu kien, chon toc do, huong dan cach choi
{
	system("cls");
	int chon = 1, choncu = 0;
	SetTeColor(11);
	gotoxy(23, 2);
	printf(">>>>>GAME RAN SAN MOI<<<<<\n");
	SetTeColor(10);
	gotoxy(32, 3);
	printf("Choi Luon");
	gotoxy(29, 4);
	printf("Chon Muc Do Choi");
	gotoxy(32, 5);
	printf("Huong Dan");
	gotoxy(32, 6);
	printf("Thong Tin\n");
	menuchon(1, 0);
	while (1)
	{
		char phim;
		if (_kbhit())
		{
			phim = _getch();
			if (phim == 13)
				break;
			if (phim == 80)
			{
				if (chon < 4)
				{
					chon++;
					choncu = chon - 1;
					menuchon(chon, choncu);
				}
			}
			if (phim == 72)
			{
				if (chon > 1)
				{
					chon--;
					choncu = chon + 1;
					menuchon(chon, choncu);
				}
			}
		}
	}
	if (chon == 1)
		return;
	if (chon == 2) // chon toc do choi phu hop
	{
		system("cls");
		char chondokho;
		printf("Bam 1 2 3 chon muc do:\n");
		printf("1.De\n");
		printf("2.Binh Thuong\n");
		printf("3.Kho");

		do
		{
			chondokho = _getch();
			if (chondokho < 49 || chondokho > 51)
				printf("Chon lai muc do: \n");
		} while (chondokho < 49 || chondokho > 51);
		system("cls");
		if (chondokho == 49)
		{
			doKho = 150;
			printf("Da chon muc do DE\n");
		}
		if (chondokho == 50)
		{
			doKho = 90;
			printf("Da chon muc do BINH THUONG\n");
		}
		if (chondokho == 51)
		{
			doKho = 40;
			printf("Da chon muc do KHO\n");
		}
		printf("Bam enter de choi game\nBam ESC de quay lai menu\n");
		char enter;
		while (1)
		{
			enter = _getch();
			if (enter == 27)
				break;
			if (enter == 13)
				return;
		}
		menu();
	}
	if (chon == 3) //huong dan cach choi
	{
		system("cls");
		printf("\tDung 4 phim a w d s de dieu khien con ran, dam dau vao tuong la chet\n");
		printf("\tKhi an duoc 5 con moi thi se xuat hien con moi dac biet\n\tton tai tron 90 buoc di cua con ran\n");
		printf("\tKhi an con moi dac biet se duoc diem rat la cao\n\n");
		printf("\tBam enter de qua lai luc nay__");
		char enter;
		while (1)
		{
			enter = _getch();
			if (enter == 13)
				break;
		}
		menu();
	}
	if (chon == 4)
	{
		intro();
	}

}
void menuchon(int chon, int choncu) //ham xu ly trong ham dieu khien
{
	if (chon == 1)
	{
		if (choncu == 2)
		{
			gotoxy(25, 4);
			printf(" ");
			gotoxy(47, 4);
			printf(" ");
		}
		gotoxy(25, 3);
		printf("%c", 16);
		gotoxy(47, 3);
		printf("%c", 17);
	}
	if (chon == 2)
	{
		if (choncu == 1)
		{
			gotoxy(25, 3);
			printf(" ");
			gotoxy(47, 3);
			printf(" ");
		}
		if (choncu == 3)
		{
			gotoxy(25, 5);
			printf(" ");
			gotoxy(47, 5);
			printf(" ");
		}
		gotoxy(25, 4);
		printf("%c", 16);
		gotoxy(47, 4);
		printf("%c", 17);
	}
	if (chon == 3)
	{
		if (choncu == 2)
		{
			gotoxy(25, 4);
			printf(" ");
			gotoxy(47, 4);
			printf(" ");
		}
		if (choncu == 4)
		{
			gotoxy(25, 6);
			printf(" ");
			gotoxy(47, 6);
			printf(" ");
		}
		gotoxy(25, 5);
		printf("%c", 16);
		gotoxy(47, 5);
		printf("%c", 17);
	}
	if (chon == 4)
	{
		if (choncu == 3)
		{
			gotoxy(25, 5);
			printf(" ");
			gotoxy(47, 5);
			printf(" ");
		}
		gotoxy(25, 6);
		printf("%c", 16);
		gotoxy(47, 6);
		printf("%c", 17);
	}
}
void reset() // ham reset lai cac thong so ban dau
{
	demTD = 0;
	demV = 90;
	DoDai = 2;
	CheckAnV = 0;
	CheckV = 0;
	ktDoAnV = 0;
	DiemCT = 0;
	DiemOLD = 0;
	DiemV = 0;
	doKho = 100;
}
