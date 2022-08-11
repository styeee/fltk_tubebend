#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Group.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Progress.H>

#include "form.h"
#pragma warning (disable:4996)

class widget:public Fl_Group
{
	const char border;
	const char beetwin=10;
	const char font=16;
	char state=0;
	
	char text[11]="0000.0000";

	Fl_Box*out;

	Fl_Button*faster;
	Fl_Button*slow;

	Fl_Button*move;
	Fl_Button*set;

	Fl_Button*zero;
	Fl_Button*home;

	Fl_Progress*info;
	Fl_Progress*speed;

public:

	widget(int x,int y,int w,int h,const char c=7,const char*name=0,const char border=5)
		:Fl_Group(x,y,w,h,name),border(border)
	{
		color(c);

		form up1{x,y,w,h};
		up1.border(border);
		form&&down1=up1.ver_div(up1.h2());

		const short finger=up1.w>>2;
		
		form&&up3=up1.gor_div(finger);
		form&&up2=up1.gor_div(finger<<1);
		form&&down4=down1.gor_div(finger);
		form&&down3=down1.gor_div(finger);
		form&&down2=down1.gor_div(finger);

		up1.border(beetwin);
		up2.border(beetwin);
		up3.border(beetwin);
		down1.border(beetwin);
		down2.border(beetwin);
		down3.border(beetwin);
		down4.border(beetwin);

		Fl::set_font(0,1);

		faster=new Fl_Button(un(up1),u8"быстрее");
			faster->labelsize(font);
			faster->align(FL_ALIGN_CLIP);
		zero=new Fl_Button(un(up3),u8"ноль\nтекущий");
			zero->labelsize(font);
			zero->align(FL_ALIGN_CLIP);
			zero->callback([](Fl_Widget*w,void*d)
			{
				((widget*)d)->set_value(500);
			},this);

		slow=new Fl_Button(un(down1),u8"медленее");
			slow->labelsize(font);
			slow->align(FL_ALIGN_CLIP);
		move=new Fl_Button(un(down2),u8"двигать");
			move->labelsize(font);
			move->align(FL_ALIGN_CLIP);
		set=new Fl_Button(un(down3),u8"установить\nтекущий");
			set->labelsize(font);
			set->align(FL_ALIGN_CLIP);
		home=new Fl_Button(un(down4),u8"калибровка");
			home->labelsize(font);
			home->align(FL_ALIGN_CLIP);

		out=new Fl_Box(un(up2),text);
		out->labelsize(font<<1);
		out->align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE|FL_ALIGN_CLIP);
		out->box(FL_FLAT_BOX);

		const short old=up2.h;
		up2.h=20;

		info=new Fl_Progress(un(up2));
		info->maximum(1000);
		info->color(8);
		//info->color2(1);
		info->box(FL_RSHADOW_BOX);

		up2.y+=(old-up2.h);

		speed=new Fl_Progress(un(up2));
		speed->maximum(2500);
		speed->color(8);
		//speed->color2(5);
		speed->box(FL_RSHADOW_BOX);

		end();
	}

	~widget()
	{
		delete faster;delete slow;delete move;
		delete set;delete zero;delete home;
	}

	void draw()
    {
         fl_rectf(x(),y(),w(),h(),color());
			for(char i=border;i--;)
		 fl_rect(x()+i,y()+i,w()-(i<<1),h()-(i<<1),0);
         Fl_Group::draw();
    }

	inline
	void set_value(const float n)
	{
		if(n>info->maximum())return;
		sprintf(text,"%4.4f",n);
		out->label(text);
		info->value(n);

		speed->redraw();
	}

	inline
	void set_max(const float n)
	{
		if(n>1000)return;
		info->maximum(n);
	}
};

int main()
{
	form fpu1={0,0,1200,800};

	Fl_Window win(fpu1.w,fpu1.h);

	form&&fo=fpu1.ver_div(fpu1.h2());
	const short cw=fpu1.w>>2;
	form&&fw=fpu1.gor_div(-cw);
	form&&fpd1=fpu1.ver_div(fpu1.h2());

	form&&fpu2=fpu1.gor_div(fpu1.w2());
	form&&fpd2=fpd1.gor_div(fpd1.w2());

	widget axis_t(un(fpu1),1,"T");
	widget axis_r(un(fpu2),2,"R");
	widget axis_b(un(fpd1),4,"B");
	Fl_Button free1(un(fpd2),"fpd2");

	//printf(Fl::get_font(0));

	Fl::scheme("plastic");

	win.end();
	win.resizable(win);
	win.show();

	return Fl::run();
}