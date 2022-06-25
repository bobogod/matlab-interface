classdef ThresholdDetector < GenericProcessor
	% ThresholdDetector An example of a filter processor that detects if the incoming data is above a certain threshold value.


	properties
		thresholdValue;
    end
  
    methods 

    	function self = ThresholdDetector(host, port)
            
            self = self@GenericProcessor(host, port);
            
            self.thresholdValue = 3.2; %V
            
			self.process();

		end

    end

	methods (Access = protected)

		function process(self)
            
            while (1)
                
                process@GenericProcessor(self); 
                k = find(self.dataIn.continuous > self.thresholdValue);
                self.dataOut = sprintf('%d ', k);
                
            end

		end

	end

end