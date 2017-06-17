#ifndef GCOM_COMPUTER_H
#define GCOM_COMPUTER_H

#include <gcom/core/node.h>
#include <gcom/utils/shared.h>
#include <gcom/core/port.h>
#include <memory>
#include <vector>
#include <thread>

namespace gcom
{
	class computer : public node
	{
	protected:
		virtual int inter_start() override final;
		virtual void inter_stop() override final;
		virtual int on_loop() = 0;
	private:
		virtual int on_start() override { return GCOM_OK; }
		virtual void on_stop() override {}

	private:
		std::vector<input*> m_inputs;
		std::vector<output*> m_outputs;
	public:
		virtual input* get_input(size_t) override final;
		virtual output* get_output(size_t) override final;
	protected:
		void add_input(std::string = "unnamed input");
		void add_output(std::string = "unnamed output");

	private:
		std::thread *m_thread;
		int m_thread_result;
		shared<bool> m_abort_thread;
		static void thread_func(computer *computer);
	};
}

#endif
