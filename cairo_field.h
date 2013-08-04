#include"field.h"
#include<cairo.h>
#include<gtk/gtk.h>
gboolean on_Timer(GtkWidget *windows){
	gtk_widget_queue_draw(windows);
	return TRUE;
}
gboolean on_draw_event (GtkWidget *widget,cairo_t *cr,gpointer data);
class cairo_field:public field{
	private:
		GtkWidget *window;
	public:
		cairo_field(control_algorithm& alg,std::vector<line> vl = *new std::vector<line>(),int *argc = 0,char*** argv = NULL,car ca = *new car()):field(alg,vl,ca){
			gtk_init (argc, argv);

			window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

			g_signal_connect (window, "draw",G_CALLBACK (on_draw_event), this);
			g_signal_connect (window, "destroy",G_CALLBACK (gtk_main_quit), NULL);

			gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
			gtk_window_set_default_size (GTK_WINDOW (window), 800,600);
			gtk_widget_set_app_paintable (window, TRUE);

			gtk_widget_show_all (window);
			g_timeout_add(1000,(GSourceFunc)on_Timer,(gpointer)window);

		}
		static void start(){
			gtk_main();	
		}
};
//TODO:绘图修正函数
gboolean on_draw_event (GtkWidget *widget,cairo_t *cr,gpointer data){
	std::vector<line> vvv = ((cairo_field*) data)->get_vline();
	car c = ((cairo_field*) data)->get_car();
	cairo_arc(cr,c.postion.x,c.postion.y,c.r,0,2*M_PI);
	cairo_move_to(cr,c.postion.x,c.postion.y);
	cairo_line_to(cr,c.postion.x + c.r * cos(c.w),c.postion.y + c.r * sin(c.w));
	cairo_set_source_rgb( cr, 0 , 0 , 0) ;
	cairo_set_line_width ( cr, 0.5) ;
	for(std::vector<line>::iterator it = vvv.begin();it != vvv.end();it++){
		cairo_move_to(cr,it->p[0].x,it->p[0].y);
		cairo_line_to(cr,it->p[1].x,it->p[1].y);
	}

	cairo_stroke( cr) ;
	return FALSE;
}
