using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

using OxyPlot;
using OxyPlot.Series;

namespace ECGapp
{
    class ViewModel
    {
        //public Communication com { get; private set; }
        public PlotModel ECGModel { get; private set; } = new PlotModel { Title = "ECG" };

        public ViewModel()
        {
            var series1 = new LineSeries { Title = "ECG", MarkerType = MarkerType.None };
            series1.Points.Add(new DataPoint(0, 0));
            series1.Points.Add(new DataPoint(10, 18));
            series1.Points.Add(new DataPoint(20, 12));
            series1.Points.Add(new DataPoint(30, 8));
            series1.Points.Add(new DataPoint(40, 15));
            
            ECGModel.Series.Add(series1);
        }
    }
}
