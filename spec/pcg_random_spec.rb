require 'spec_helper'

# This set of tests is for the user facing functions
#

describe PCGRandom do
  context '::new_seed' do
    
    it 'returns a strictly positive value' do
      expect(PCGRandom.new_seed).to > 0
    end
    
    it 'returns an Integral value' do
      
    end
  end
end
