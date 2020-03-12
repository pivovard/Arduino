using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

using OxyPlot;
using OxyPlot.Axes;
using OxyPlot.Series;

namespace ECGapp
{
    class ViewModel 
    {
        
        public PlotModel ECGPlot { get; private set; } = new PlotModel { Title = "ECG" };
        private LineSeries ecg_series = new LineSeries { Title = "ECG", MarkerType = MarkerType.None, Color = OxyColors.Red };
        public PlotModel SpeedPlot { get; private set; } = new PlotModel { Title = "Heart rate" };
        private LineSeries speed_series = new LineSeries { Title = "HR", MarkerType = MarkerType.None };

        private const int N = 100;

        public ViewModel()
        {
            ECGPlot.Series.Add(ecg_series);
            ECGPlot.Axes.Add(new LinearAxis() { Position = AxisPosition.Bottom, Title = "time [s]" });
            ECGPlot.Axes.Add(new LinearAxis() { Position = AxisPosition.Left, Title = "[mV]" });

            SpeedPlot.Series.Add(speed_series);
            SpeedPlot.Axes.Add(new LinearAxis() { Position = AxisPosition.Bottom, Title = "time [s]" });
            SpeedPlot.Axes.Add(new LinearAxis() { Position = AxisPosition.Left, Title = "[bpm]" });
        }

        public void Add(ECGcom.Item item)
        {
            Add(item.time, item.ecg, item.speed);
        }

        public void Add(float time, float ecg, float speed)
        {
            ecg_series.Points.Add(new DataPoint(time, ecg));
            speed_series.Points.Add(new DataPoint(time, speed));
            if (ecg_series.Points.Count > N)
            {
                ecg_series.Points.RemoveAt(0);
                speed_series.Points.RemoveAt(0);
            }
            ECGPlot.InvalidatePlot(true);
            SpeedPlot.InvalidatePlot(true);
        }

        

    }
}
