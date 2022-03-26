using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


namespace MDJ
{

    //UserData的定义：
    class PointData
    {
        private int _id;
        private double _x_value;
        private double _y_value;
        private double _h_value;
        private double _t_value;


        public int id
        {
            get { return _id; }
            set
            {
                _id = value;
            }
        }
        public double x_value
        {
            get { return _x_value; }
            set
            {
                _x_value = value;
            }
        }
        public double y_value
        {
            get { return _y_value; }
            set
            {
                _y_value = value;
            }
        }
        public double h_value
        {
            get { return _h_value; }
            set
            {
                _h_value = value;
            }
        }
        public double t_value
        {
            get { return _t_value; }
            set
            {
                _t_value = value;
            }
        }

        public PointData(int id, double x_value, double y_value,double h_value,double t_value)
        {
            _id = id;
            _x_value = x_value;
            _y_value = y_value;
            _h_value = h_value;
            _t_value = t_value;
        }

    }
}
